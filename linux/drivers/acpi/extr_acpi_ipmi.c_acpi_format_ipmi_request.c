#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kernel_ipmi_msg {scalar_t__ data_len; int /*<<< orphan*/  data; int /*<<< orphan*/  cmd; int /*<<< orphan*/  netfn; } ;
struct TYPE_2__ {scalar_t__* data; int /*<<< orphan*/  channel; int /*<<< orphan*/  addr_type; } ;
struct acpi_ipmi_msg {scalar_t__ tx_msgid; struct acpi_ipmi_device* device; TYPE_1__ addr; int /*<<< orphan*/  data; struct kernel_ipmi_msg tx_message; } ;
struct acpi_ipmi_device {int /*<<< orphan*/  tx_msg_lock; scalar_t__ curr_msgid; int /*<<< orphan*/  dev; } ;
struct acpi_ipmi_buffer {scalar_t__ length; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  acpi_physical_address ;
typedef  int /*<<< orphan*/  acpi_integer ;

/* Variables and functions */
 scalar_t__ ACPI_IPMI_MAX_MSG_LENGTH ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPMI_BMC_CHANNEL ; 
 int /*<<< orphan*/  IPMI_OP_RGN_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPMI_OP_RGN_NETFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 int /*<<< orphan*/  dev_WARN_ONCE (int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int acpi_format_ipmi_request(struct acpi_ipmi_msg *tx_msg,
				    acpi_physical_address address,
				    acpi_integer *value)
{
	struct kernel_ipmi_msg *msg;
	struct acpi_ipmi_buffer *buffer;
	struct acpi_ipmi_device *device;
	unsigned long flags;

	msg = &tx_msg->tx_message;

	/*
	 * IPMI network function and command are encoded in the address
	 * within the IPMI OpRegion; see ACPI 4.0, sec 5.5.2.4.3.
	 */
	msg->netfn = IPMI_OP_RGN_NETFN(address);
	msg->cmd = IPMI_OP_RGN_CMD(address);
	msg->data = tx_msg->data;

	/*
	 * value is the parameter passed by the IPMI opregion space handler.
	 * It points to the IPMI request message buffer
	 */
	buffer = (struct acpi_ipmi_buffer *)value;

	/* copy the tx message data */
	if (buffer->length > ACPI_IPMI_MAX_MSG_LENGTH) {
		dev_WARN_ONCE(tx_msg->device->dev, true,
			      "Unexpected request (msg len %d).\n",
			      buffer->length);
		return -EINVAL;
	}
	msg->data_len = buffer->length;
	memcpy(tx_msg->data, buffer->data, msg->data_len);

	/*
	 * now the default type is SYSTEM_INTERFACE and channel type is BMC.
	 * If the netfn is APP_REQUEST and the cmd is SEND_MESSAGE,
	 * the addr type should be changed to IPMB. Then we will have to parse
	 * the IPMI request message buffer to get the IPMB address.
	 * If so, please fix me.
	 */
	tx_msg->addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	tx_msg->addr.channel = IPMI_BMC_CHANNEL;
	tx_msg->addr.data[0] = 0;

	/* Get the msgid */
	device = tx_msg->device;

	spin_lock_irqsave(&device->tx_msg_lock, flags);
	device->curr_msgid++;
	tx_msg->tx_msgid = device->curr_msgid;
	spin_unlock_irqrestore(&device->tx_msg_lock, flags);

	return 0;
}
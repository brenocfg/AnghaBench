#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* uint8_t ;
struct libusb_device_handle {int dummy; } ;
struct iwmbt_hci_cmd {void** data; void* length; int /*<<< orphan*/  opcode; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  IWMBT_BULK_IN_ENDPOINT_ADDR ; 
 int /*<<< orphan*/  IWMBT_BULK_OUT_ENDPOINT_ADDR ; 
 int IWMBT_HCI_CMD_SIZE (struct iwmbt_hci_cmd*) ; 
 int IWMBT_HCI_MAX_CMD_SIZE ; 
 int /*<<< orphan*/  htole16 (int) ; 
 int /*<<< orphan*/  iwmbt_err (char*,int /*<<< orphan*/ ,...) ; 
 int libusb_bulk_transfer (struct libusb_device_handle*,int /*<<< orphan*/ ,void**,int,int*,int) ; 
 int /*<<< orphan*/  libusb_strerror (int) ; 
 int /*<<< orphan*/  memcpy (void**,void const*,void*) ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwmbt_send_fragment(struct libusb_device_handle *hdl,
    uint8_t fragment_type, const void *data, uint8_t len, int timeout)
{
	int ret, transferred;
	uint8_t buf[IWMBT_HCI_MAX_CMD_SIZE];
	struct iwmbt_hci_cmd *cmd = (struct iwmbt_hci_cmd *) buf;

	memset(buf, 0, sizeof(buf));
	cmd->opcode = htole16(0xfc09),
	cmd->length = len + 1,
	cmd->data[0] = fragment_type;
	memcpy(cmd->data + 1, data, len);

	ret = libusb_bulk_transfer(hdl,
	    IWMBT_BULK_OUT_ENDPOINT_ADDR,
	    (uint8_t *)cmd,
	    IWMBT_HCI_CMD_SIZE(cmd),
	    &transferred,
	    timeout);

	if (ret < 0 || transferred != (int)IWMBT_HCI_CMD_SIZE(cmd)) {
		iwmbt_err("libusb_bulk_transfer() failed: err=%s, size=%zu",
		    libusb_strerror(ret),
		    IWMBT_HCI_CMD_SIZE(cmd));
		return (-1);
	}

	ret = libusb_bulk_transfer(hdl,
	    IWMBT_BULK_IN_ENDPOINT_ADDR,
	    buf,
	    sizeof(buf),
	    &transferred,
	    timeout);

	if (ret < 0) {
		iwmbt_err("libusb_bulk_transfer() failed: err=%s",
		    libusb_strerror(ret));
		return (-1);
	}

	return (0);
}
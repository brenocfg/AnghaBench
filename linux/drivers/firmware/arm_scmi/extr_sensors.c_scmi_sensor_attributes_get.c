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
typedef  int u64 ;
struct sensors_info {int reg_addr; int reg_size; int /*<<< orphan*/  max_requests; int /*<<< orphan*/  num_sensors; } ;
struct TYPE_2__ {struct scmi_msg_resp_sensor_attributes* buf; } ;
struct scmi_xfer {TYPE_1__ rx; } ;
struct scmi_msg_resp_sensor_attributes {int /*<<< orphan*/  reg_size; int /*<<< orphan*/  reg_addr_high; int /*<<< orphan*/  reg_addr_low; int /*<<< orphan*/  max_requests; int /*<<< orphan*/  num_sensors; } ;
struct scmi_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_ATTRIBUTES ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_SENSOR ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

__attribute__((used)) static int scmi_sensor_attributes_get(const struct scmi_handle *handle,
				      struct sensors_info *si)
{
	int ret;
	struct scmi_xfer *t;
	struct scmi_msg_resp_sensor_attributes *attr;

	ret = scmi_xfer_get_init(handle, PROTOCOL_ATTRIBUTES,
				 SCMI_PROTOCOL_SENSOR, 0, sizeof(*attr), &t);
	if (ret)
		return ret;

	attr = t->rx.buf;

	ret = scmi_do_xfer(handle, t);
	if (!ret) {
		si->num_sensors = le16_to_cpu(attr->num_sensors);
		si->max_requests = attr->max_requests;
		si->reg_addr = le32_to_cpu(attr->reg_addr_low) |
				(u64)le32_to_cpu(attr->reg_addr_high) << 32;
		si->reg_size = le32_to_cpu(attr->reg_size);
	}

	scmi_xfer_put(handle, t);
	return ret;
}
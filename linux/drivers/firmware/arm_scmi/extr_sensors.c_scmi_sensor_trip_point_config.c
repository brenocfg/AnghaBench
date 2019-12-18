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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {struct scmi_msg_set_sensor_trip_point* buf; } ;
struct scmi_xfer {TYPE_1__ tx; } ;
struct scmi_msg_set_sensor_trip_point {void* value_high; void* value_low; void* event_control; void* id; } ;
struct scmi_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCMI_PROTOCOL_SENSOR ; 
 int SENSOR_TP_BOTH ; 
 int SENSOR_TP_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SENSOR_TRIP_POINT_CONFIG ; 
 void* cpu_to_le32 (int) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

__attribute__((used)) static int
scmi_sensor_trip_point_config(const struct scmi_handle *handle, u32 sensor_id,
			      u8 trip_id, u64 trip_value)
{
	int ret;
	u32 evt_cntl = SENSOR_TP_BOTH;
	struct scmi_xfer *t;
	struct scmi_msg_set_sensor_trip_point *trip;

	ret = scmi_xfer_get_init(handle, SENSOR_TRIP_POINT_CONFIG,
				 SCMI_PROTOCOL_SENSOR, sizeof(*trip), 0, &t);
	if (ret)
		return ret;

	trip = t->tx.buf;
	trip->id = cpu_to_le32(sensor_id);
	trip->event_control = cpu_to_le32(evt_cntl | SENSOR_TP_ID(trip_id));
	trip->value_low = cpu_to_le32(trip_value & 0xffffffff);
	trip->value_high = cpu_to_le32(trip_value >> 32);

	ret = scmi_do_xfer(handle, t);

	scmi_xfer_put(handle, t);
	return ret;
}
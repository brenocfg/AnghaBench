#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct sensors_info {struct scmi_sensor_info* sensors; } ;
struct TYPE_4__ {void* buf; } ;
struct TYPE_3__ {struct scmi_msg_sensor_reading_get* buf; } ;
struct scmi_xfer {TYPE_2__ rx; TYPE_1__ tx; } ;
struct scmi_sensor_info {scalar_t__ async; } ;
struct scmi_msg_sensor_reading_get {void* flags; void* id; } ;
struct scmi_handle {struct sensors_info* sensor_priv; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  SCMI_PROTOCOL_SENSOR ; 
 int /*<<< orphan*/  SENSOR_READING_GET ; 
 int SENSOR_READ_ASYNC ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  get_unaligned_le64 (void*) ; 
 int scmi_do_xfer (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_do_xfer_with_response (struct scmi_handle const*,struct scmi_xfer*) ; 
 int scmi_xfer_get_init (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct scmi_xfer**) ; 
 int /*<<< orphan*/  scmi_xfer_put (struct scmi_handle const*,struct scmi_xfer*) ; 

__attribute__((used)) static int scmi_sensor_reading_get(const struct scmi_handle *handle,
				   u32 sensor_id, u64 *value)
{
	int ret;
	struct scmi_xfer *t;
	struct scmi_msg_sensor_reading_get *sensor;
	struct sensors_info *si = handle->sensor_priv;
	struct scmi_sensor_info *s = si->sensors + sensor_id;

	ret = scmi_xfer_get_init(handle, SENSOR_READING_GET,
				 SCMI_PROTOCOL_SENSOR, sizeof(*sensor),
				 sizeof(u64), &t);
	if (ret)
		return ret;

	sensor = t->tx.buf;
	sensor->id = cpu_to_le32(sensor_id);

	if (s->async) {
		sensor->flags = cpu_to_le32(SENSOR_READ_ASYNC);
		ret = scmi_do_xfer_with_response(handle, t);
		if (!ret)
			*value = get_unaligned_le64((void *)
						    ((__le32 *)t->rx.buf + 1));
	} else {
		sensor->flags = cpu_to_le32(0);
		ret = scmi_do_xfer(handle, t);
		if (!ret)
			*value = get_unaligned_le64(t->rx.buf);
	}

	scmi_xfer_put(handle, t);
	return ret;
}
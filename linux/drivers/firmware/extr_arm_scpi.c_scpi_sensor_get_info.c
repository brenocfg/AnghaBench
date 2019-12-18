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
typedef  int /*<<< orphan*/  u16 ;
struct scpi_sensor_info {int /*<<< orphan*/  sensor_id; } ;
struct _scpi_sensor_info {int /*<<< orphan*/  sensor_id; } ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  _info ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SENSOR_INFO ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct scpi_sensor_info*,struct _scpi_sensor_info*,int) ; 
 int scpi_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct _scpi_sensor_info*,int) ; 

__attribute__((used)) static int scpi_sensor_get_info(u16 sensor_id, struct scpi_sensor_info *info)
{
	__le16 id = cpu_to_le16(sensor_id);
	struct _scpi_sensor_info _info;
	int ret;

	ret = scpi_send_message(CMD_SENSOR_INFO, &id, sizeof(id),
				&_info, sizeof(_info));
	if (!ret) {
		memcpy(info, &_info, sizeof(*info));
		info->sensor_id = le16_to_cpu(_info.sensor_id);
	}

	return ret;
}
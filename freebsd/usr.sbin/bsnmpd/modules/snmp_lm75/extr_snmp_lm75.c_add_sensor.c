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
typedef  int /*<<< orphan*/  temp ;
struct lm75_snmp_sensor {int sysctlidx; int temp; scalar_t__ index; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct lm75_snmp_sensor*,int /*<<< orphan*/ ) ; 
 int TZ_ZEROC ; 
 struct lm75_snmp_sensor* calloc (int,int) ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ lm75_sensors ; 
 int /*<<< orphan*/  sensors ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  update_sensor (struct lm75_snmp_sensor*,int) ; 
 scalar_t__ update_sensor_sysctl (int*,size_t*,int,char*) ; 

__attribute__((used)) static int
add_sensor(char *buf)
{
	int idx, temp;
	size_t len;
	struct lm75_snmp_sensor *sensor;

	if (sscanf(buf, "dev.lm75.%d.temperature", &idx) != 1)
		return (-1);

	/* Read the sensor temperature. */
	len = sizeof(temp);
	if (update_sensor_sysctl(&temp, &len, idx, "temperature") != 0)
		return (-1);

	/* Add the sensor data to the table. */
	sensor = calloc(1, sizeof(*sensor));
	if (sensor == NULL) {
		syslog(LOG_ERR, "Unable to allocate %zu bytes for resource",
		    sizeof(*sensor));
		return (-1);
	}
	sensor->index = ++lm75_sensors;
	sensor->sysctlidx = idx;
	sensor->temp = (temp - TZ_ZEROC) / 10;
	TAILQ_INSERT_TAIL(&sensors, sensor, link);

	update_sensor(sensor, idx);

	return (0);
}
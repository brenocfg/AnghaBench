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
struct lm75_snmp_sensor {int dummy; } ;

/* Variables and functions */
 struct lm75_snmp_sensor* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct lm75_snmp_sensor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct lm75_snmp_sensor*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  sensors ; 

__attribute__((used)) static void
free_sensors(void)
{
	struct lm75_snmp_sensor *sensor;

	while ((sensor = TAILQ_FIRST(&sensors)) != NULL) {
		TAILQ_REMOVE(&sensors, sensor, link);
		free(sensor);
	}
}
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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int LM75BUF ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ UPDATE_INTERVAL ; 
 scalar_t__ add_sensor (char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  free_sensors () ; 
 scalar_t__ get_ticks () ; 
 scalar_t__ last_sensors_update ; 
 scalar_t__ lm75_sensors ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 int sysctlgetnext (int*,size_t,int*,size_t*) ; 
 scalar_t__ sysctlname (int*,size_t,char*,int) ; 
 int sysctlnametomib (char*,int*,size_t*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static int
update_sensors(void)
{
	char buf[LM75BUF];
	int i, root[5], *next, *oid;
	size_t len, nextlen, rootlen;
	static uint64_t now;

	now = get_ticks();
	if (now - last_sensors_update < UPDATE_INTERVAL)
		return (0);

	last_sensors_update = now;

	/* Reset the sensor data. */
	free_sensors();
	lm75_sensors = 0;

	/* Start from the lm75 default root node. */
	rootlen = 2;
	if (sysctlnametomib("dev.lm75", root, &rootlen) == -1)
		return (0);

	oid = (int *)malloc(sizeof(int) * rootlen);
	if (oid == NULL) {
		perror("malloc");
		return (-1);
	}
	memcpy(oid, root, rootlen * sizeof(int));
	len = rootlen;

	/* Traverse the sysctl(3) interface and find the active sensors. */
	for (;;) {

		/* Find the size of the next mib. */
		nextlen = 0;
		if (sysctlgetnext(oid, len, NULL, &nextlen) == -1) {
			free(oid);
			return (0);
		}
		/* Alocate and read the next mib. */
		next = (int *)malloc(nextlen);
		if (next == NULL) {
			syslog(LOG_ERR,
			    "Unable to allocate %zu bytes for resource",
			    nextlen);
			free(oid);
			return (-1);
		}
		if (sysctlgetnext(oid, len, next, &nextlen) == -1) {
			free(oid);
			free(next);
			return (0);
		}
		free(oid);
		/* Check if we care about the next mib. */
		for (i = 0; i < (int)rootlen; i++)
			if (next[i] != root[i]) {
				free(next);
				return (0);
			}
		oid = (int *)malloc(nextlen);
		if (oid == NULL) {
			syslog(LOG_ERR,
			    "Unable to allocate %zu bytes for resource",
			    nextlen);
			free(next);
			return (-1);
		}
		memcpy(oid, next, nextlen);
		free(next);
		len = nextlen / sizeof(int);

		/* Find the mib name. */
		if (sysctlname(oid, len, buf, sizeof(buf)) != 0)
			continue;

		if (strstr(buf, "temperature"))
			if (add_sensor(buf) != 0) {
				free(oid);
				return (-1);
			}
	}

	return (0);
}
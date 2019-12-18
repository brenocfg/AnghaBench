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
typedef  int /*<<< orphan*/  mib ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int LM75BUF ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char const*) ; 
 int sysctl (int*,size_t,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sysctlnametomib (char*,int*,size_t*) ; 

__attribute__((used)) static int
update_sensor_sysctl(void *obuf, size_t *obuflen, int idx, const char *name)
{
	char buf[LM75BUF];
	int mib[5];
	size_t len;

	/* Fill out the mib information. */
	snprintf(buf, sizeof(buf) - 1, "dev.lm75.%d.%s", idx, name);
	len = sizeof(mib) / sizeof(int);
	if (sysctlnametomib(buf, mib, &len) == -1)
		return (-1);

	if (len != 4)
		return (-1);

	/* Read the sysctl data. */
	if (sysctl(mib, len, obuf, obuflen, NULL, 0) == -1)
		return (-1);

	return (0);
}
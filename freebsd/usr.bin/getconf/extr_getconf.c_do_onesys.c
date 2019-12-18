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

/* Variables and functions */
 scalar_t__ errno ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 long sysconf (int) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static void
do_onesys(const char *name, int key)
{
	long value;

	errno = 0;
	value = sysconf(key);
	if (value == -1 && errno != 0) {
		warn("sysconf: %s", name);
		return;
	}
	printf("%s: ", name);
	if (value == -1)
		printf("undefined\n");
	else
		printf("%ld\n", value);
}
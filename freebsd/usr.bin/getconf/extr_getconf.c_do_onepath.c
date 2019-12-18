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
 scalar_t__ EINVAL ; 
 scalar_t__ errno ; 
 long pathconf (char const*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static void
do_onepath(const char *name, int key, const char *path)
{
	long value;

	errno = 0;
	value = pathconf(path, key);
	if (value == -1 && errno != EINVAL && errno != 0)
		warn("pathconf: %s", name);
	printf("%s: ", name);
	if (value == -1)
		printf("undefined\n");
	else
		printf("%ld\n", value);
}
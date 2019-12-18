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
 size_t confstr (int,char*,size_t) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static void
do_onestr(const char *name, int key)
{
	size_t len;

	errno = 0;
	len = confstr(key, 0, 0);
	if (len == 0 && errno != 0) {
		warn("confstr: %s", name);
		return;
	}
	printf("%s: ", name);
	if (len == 0)
		printf("undefined\n");
	else {
		char buf[len + 1];

		confstr(key, buf, len);
		printf("%s\n", buf);
	}
}
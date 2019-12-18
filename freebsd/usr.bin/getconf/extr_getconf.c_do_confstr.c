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
 int /*<<< orphan*/  EX_OSERR ; 
 size_t confstr (int,char*,size_t) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 int errno ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
do_confstr(const char *name, int key)
{
	size_t len;
	int savederr;

	savederr = errno;
	errno = 0;
	len = confstr(key, 0, 0);
	if (len == 0) {
		if (errno)
			err(EX_OSERR, "confstr: %s", name);
		else
			printf("undefined\n");
	} else {
		char buf[len + 1];

		confstr(key, buf, len);
		printf("%s\n", buf);
	}
	errno = savederr;
}
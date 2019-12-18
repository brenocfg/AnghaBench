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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 char* strdup (char*) ; 

__attribute__((used)) static char *
args2line(int argc, char **argv)
{
	char *cp1, *cend;
	const char *cp2;
	char buf[1024];

	if (argc <= 0)
		return strdup("\n");

	cp1 = buf;
	cend = buf + sizeof(buf) - 1;		/* save room for '\0' */
	while (--argc >= 0) {
		cp2 = *argv++;
		while ((cp1 < cend) && (*cp1++ = *cp2++))
			;
		cp1[-1] = ' ';
	}
	cp1[-1] = '\n';
	*cp1 = '\0';
	return strdup(buf);
}
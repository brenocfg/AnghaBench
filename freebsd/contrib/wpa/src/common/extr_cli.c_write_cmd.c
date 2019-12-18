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
 int os_snprintf (char*,int,char*,char const*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int write_cmd(char *buf, size_t buflen, const char *cmd, int argc, char *argv[])
{
	int i, res;
	char *pos, *end;

	pos = buf;
	end = buf + buflen;

	res = os_snprintf(pos, end - pos, "%s", cmd);
	if (os_snprintf_error(end - pos, res))
		goto fail;
	pos += res;

	for (i = 0; i < argc; i++) {
		res = os_snprintf(pos, end - pos, " %s", argv[i]);
		if (os_snprintf_error(end - pos, res))
			goto fail;
		pos += res;
	}

	buf[buflen - 1] = '\0';
	return 0;

fail:
	printf("Too long command\n");
	return -1;
}
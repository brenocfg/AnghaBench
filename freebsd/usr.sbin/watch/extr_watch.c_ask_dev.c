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
 int DEV_NAME_LEN ; 
 int /*<<< orphan*/  clear () ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_tty () ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  unset_tty () ; 

void
ask_dev(char *dbuf, const char *msg)
{
	char		buf[DEV_NAME_LEN];
	int		len;

	clear();
	unset_tty();

	if (msg)
		printf("%s\n", msg);
	if (dbuf)
		printf("Enter device name [%s]:", dbuf);
	else
		printf("Enter device name:");

	if (fgets(buf, DEV_NAME_LEN - 1, stdin)) {
		len = strlen(buf);
		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';
		if (buf[0] != '\0' && buf[0] != ' ')
			strcpy(dbuf, buf);
	}
	set_tty();
}
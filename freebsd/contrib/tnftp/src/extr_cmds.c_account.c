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
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int code ; 
 int /*<<< orphan*/  command (char*,char*) ; 
 char* getpass (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void
account(int argc, char *argv[])
{
	char *ap;
	char emptypass[] = "";

	if (argc == 0 || argc > 2) {
		UPRINTF("usage: %s [password]\n", argv[0]);
		code = -1;
		return;
	}
	else if (argc == 2)
		ap = argv[1];
	else {
		ap = getpass("Account:");
		if (ap == NULL)
			ap = emptypass;
	}
	(void)command("ACCT %s", ap);
	memset(ap, 0, strlen(ap));
}
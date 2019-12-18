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
typedef  int /*<<< orphan*/  pwd2 ;
typedef  int /*<<< orphan*/  pwd1 ;

/* Variables and functions */
 int EX_OK ; 
 int EX_USAGE ; 
 int /*<<< orphan*/  OFWO_MAXPWD ; 
 int RPP_ECHO_OFF ; 
 int RPP_REQUIRE_TTY ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  ofw_optnode (int) ; 
 int /*<<< orphan*/  ofw_setprop (int,int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * readpassphrase (char*,char*,int,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
ofwo_setpass(int fd)
{
	char pwd1[OFWO_MAXPWD + 1], pwd2[OFWO_MAXPWD + 1];

	if (readpassphrase("New password:", pwd1, sizeof(pwd1),
	    RPP_ECHO_OFF | RPP_REQUIRE_TTY) == NULL ||
	    readpassphrase("Retype new password:", pwd2, sizeof(pwd2),
	    RPP_ECHO_OFF | RPP_REQUIRE_TTY) == NULL)
		errx(EX_USAGE, "failed to get password.");
	if (strlen(pwd1) == 0) {
		printf("Password unchanged.\n");
		return (EX_OK);
	}
	if (strcmp(pwd1, pwd2) != 0) {
		printf("Mismatch - password unchanged.\n");
		return (EX_USAGE);
	}
	ofw_setprop(fd, ofw_optnode(fd), "security-password", pwd1,
	    strlen(pwd1) + 1);
	return (EX_OK);
}
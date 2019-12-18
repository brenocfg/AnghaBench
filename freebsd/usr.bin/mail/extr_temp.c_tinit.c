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
 scalar_t__ PATHSIZE ; 
 char* _PATH_TMP ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 char* getenv (char*) ; 
 scalar_t__ getuserid (char*) ; 
 char* homedir ; 
 char* myname ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 scalar_t__ rcvmode ; 
 char* savestr (char*) ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 
 char* tmpdir ; 
 char* username () ; 

void
tinit(void)
{
	char *cp;

	if ((tmpdir = getenv("TMPDIR")) == NULL || *tmpdir == '\0')
		tmpdir = _PATH_TMP;
	if ((tmpdir = strdup(tmpdir)) == NULL)
		errx(1, "Out of memory");
	/* Strip trailing '/' if necessary */
	cp = tmpdir + strlen(tmpdir) - 1;
	while (cp > tmpdir && *cp == '/') {
		*cp = '\0';
		cp--;
	}

	/*
	 * It's okay to call savestr in here because main will
	 * do a spreserve() after us.
	 */
	if (myname != NULL) {
		if (getuserid(myname) < 0)
			errx(1, "\"%s\" is not a user of this system", myname);
	} else {
		if ((cp = username()) == NULL) {
			myname = "ubluit";
			if (rcvmode)
				errx(1, "Who are you!?");
		} else
			myname = savestr(cp);
	}
	if ((cp = getenv("HOME")) == NULL || *cp == '\0' ||
	    strlen(cp) >= PATHSIZE)
		homedir = NULL;
	else
		homedir = savestr(cp);
	if (debug)
		printf("user = %s, homedir = %s\n", myname,
		    homedir ? homedir : "NONE");
}
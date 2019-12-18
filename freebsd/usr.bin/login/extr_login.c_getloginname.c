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
 int EOF ; 
 int MAXLOGNAME ; 
 int /*<<< orphan*/  NO_SLEEP_EXIT ; 
 scalar_t__ PAM_SILENT ; 
 int /*<<< orphan*/  badlogin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int getchar () ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pam_silent ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* prompt ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  username ; 

__attribute__((used)) static char *
getloginname(void)
{
	char *nbuf, *p;
	int ch;

	nbuf = malloc(MAXLOGNAME);
	if (nbuf == NULL)
		err(1, "malloc()");
	do {
		(void)printf("%s", prompt);
		for (p = nbuf; (ch = getchar()) != '\n'; ) {
			if (ch == EOF) {
				badlogin(username);
				bail(NO_SLEEP_EXIT, 0);
			}
			if (p < nbuf + MAXLOGNAME - 1)
				*p++ = ch;
		}
	} while (p == nbuf);

	*p = '\0';
	if (nbuf[0] == '-') {
		pam_silent = 0;
		memmove(nbuf, nbuf + 1, strlen(nbuf));
	} else {
		pam_silent = PAM_SILENT;
	}
	return nbuf;
}
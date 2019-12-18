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
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  REG_BASIC ; 
 int /*<<< orphan*/  YESEXPR ; 
 int /*<<< orphan*/  _PATH_TTY ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nl_langinfo (int /*<<< orphan*/ ) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regexec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
prompt(void)
{
	regex_t cre;
	size_t rsize;
	int match;
	char *response;
	FILE *ttyfp;

	if ((ttyfp = fopen(_PATH_TTY, "r")) == NULL)
		return (2);	/* Indicate that the TTY failed to open. */
	(void)fprintf(stderr, "?...");
	(void)fflush(stderr);
	if ((response = fgetln(ttyfp, &rsize)) == NULL ||
	    regcomp(&cre, nl_langinfo(YESEXPR), REG_BASIC) != 0) {
		(void)fclose(ttyfp);
		return (0);
	}
	response[rsize - 1] = '\0';
	match = regexec(&cre, response, 0, NULL, 0);
	(void)fclose(ttyfp);
	regfree(&cre);
	return (match == 0);
}
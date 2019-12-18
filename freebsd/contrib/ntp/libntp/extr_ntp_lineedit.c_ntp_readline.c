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
typedef  int /*<<< orphan*/  line_buf ;

/* Variables and functions */
 int /*<<< orphan*/  H_ENTER ; 
 int MAXEDITLINE ; 
 int /*<<< orphan*/  add_history (char*) ; 
 char* el_gets (int /*<<< orphan*/ ,int*) ; 
 char* estrdup (char const*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hev ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 char* lineedit_prompt ; 
 int /*<<< orphan*/  ntp_el ; 
 int /*<<< orphan*/  ntp_hist ; 
 int /*<<< orphan*/  ntp_readline_initted ; 
 char* readline (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char*) ; 

char *
ntp_readline(
	int *	pcount
	)
{
	char *		line;
#ifdef LE_NONE
	char		line_buf[MAXEDITLINE];
#endif
#ifdef LE_EDITLINE
	const char *	cline;
#endif

	if (!ntp_readline_initted)
		return NULL;

	*pcount = 0;

#ifdef LE_READLINE
	line = readline(lineedit_prompt ? lineedit_prompt : "");
	if (NULL != line) {
		if (*line) {
			add_history(line);
		}
		*pcount = strlen(line);
	}
#endif	/* LE_READLINE */

#ifdef LE_EDITLINE
	cline = el_gets(ntp_el, pcount);

	if (NULL != cline) {
		history(ntp_hist, &hev, H_ENTER, cline);
		line = estrdup(cline);
	} else if (*pcount == -1) {
		line = NULL;
	} else {
		line = estrdup("");
	}
#endif	/* LE_EDITLINE */

#ifdef LE_NONE
					/* stone hammers */
	if (lineedit_prompt) {
# ifdef VMS
			/*
			 * work around problem mixing
			 * stdout & stderr
			 */
			fputs("", stdout);
# endif	/* VMS */

		fputs(lineedit_prompt, stderr);
		fflush(stderr);
	}

	line = fgets(line_buf, sizeof(line_buf), stdin);
	if (NULL != line && *line) {
		*pcount = (int)strlen(line); /* cannot overflow here */
		line = estrdup(line);
	} else
		line = NULL;

#endif	/* LE_NONE */


	if (!line)			/* EOF */
		fputs("\n", stderr);

	return line;
}
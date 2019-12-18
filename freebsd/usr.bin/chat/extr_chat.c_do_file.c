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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int STR_LEN ; 
 int /*<<< orphan*/  chat_expect (char*) ; 
 int /*<<< orphan*/  chat_send (char*) ; 
 int /*<<< orphan*/  fatal (int,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* strchr (char*,char) ; 

void
do_file(char *chatfile)
{
    int linect, sendflg;
    char *sp, *arg, quote;
    char buf [STR_LEN];
    FILE *cfp;

    cfp = fopen (chatfile, "r");
    if (cfp == NULL)
	fatal(1, "%s -- open failed: %m", chatfile);

    linect = 0;
    sendflg = 0;

    while (fgets(buf, STR_LEN, cfp) != NULL) {
	sp = strchr (buf, '\n');
	if (sp)
	    *sp = '\0';

	linect++;
	sp = buf;

        /* lines starting with '#' are comments. If a real '#'
           is to be expected, it should be quoted .... */
        if ( *sp == '#' )
	    continue;

	while (*sp != '\0') {
	    if (*sp == ' ' || *sp == '\t') {
		++sp;
		continue;
	    }

	    if (*sp == '"' || *sp == '\'') {
		quote = *sp++;
		arg = sp;
		while (*sp != quote) {
		    if (*sp == '\0')
			fatal(1, "unterminated quote (line %d)", linect);

		    if (*sp++ == '\\') {
			if (*sp != '\0')
			    ++sp;
		    }
		}
	    }
	    else {
		arg = sp;
		while (*sp != '\0' && *sp != ' ' && *sp != '\t')
		    ++sp;
	    }

	    if (*sp != '\0')
		*sp++ = '\0';

	    if (sendflg)
		chat_send (arg);
	    else
		chat_expect (arg);
	    sendflg = !sendflg;
	}
    }
    fclose (cfp);
}
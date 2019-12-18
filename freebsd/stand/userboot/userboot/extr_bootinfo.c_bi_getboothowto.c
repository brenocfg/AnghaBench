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
 int RB_MULTIPLE ; 
 int RB_MUTE ; 
 int RB_SERIAL ; 
 int boot_env_to_howto () ; 
 int boot_parse_cmdline (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 

int
bi_getboothowto(char *kargs)
{
    char	*curpos, *next, *string;
    int		howto;
    int		vidconsole;

    howto = boot_parse_cmdline(kargs);
    howto |= boot_env_to_howto();

    /* Enable selected consoles */
    string = next = strdup(getenv("console"));
    vidconsole = 0;
    while (next != NULL) {
	curpos = strsep(&next, " ,");
	if (*curpos == '\0')
		continue;
	if (!strcmp(curpos, "vidconsole"))
	    vidconsole = 1;
	else if (!strcmp(curpos, "comconsole"))
	    howto |= RB_SERIAL;
	else if (!strcmp(curpos, "nullconsole"))
	    howto |= RB_MUTE;
    }

    if (vidconsole && (howto & RB_SERIAL))
	howto |= RB_MULTIPLE;

    /*
     * XXX: Note that until the kernel is ready to respect multiple consoles
     * for the messages from /etc/rc, the first named console is the primary
     * console
     */
    if (!strcmp(string, "vidconsole"))
	howto &= ~RB_SERIAL;

    free(string);

    return(howto);
}
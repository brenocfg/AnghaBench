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
typedef  int /*<<< orphan*/  time_t ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  FMT_PROMPT ; 
 char* Prompt ; 
 char* RPrompt ; 
 int /*<<< orphan*/  STRprompt ; 
 int /*<<< orphan*/  STRprompt2 ; 
 int /*<<< orphan*/  STRprompt3 ; 
 int /*<<< orphan*/  STRrprompt ; 
 int /*<<< orphan*/  SetAttributes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  editing ; 
 int /*<<< orphan*/  flush () ; 
 int /*<<< orphan*/  putraw (char) ; 
 int /*<<< orphan*/  putwraw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 char* tprintf (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* varval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (char*) ; 

void
printprompt(int promptno, const char *str)
{
    static  const Char *ocp = NULL;
    static  const char *ostr = NULL;
    time_t  lclock = time(NULL);
    const Char *cp;

    switch (promptno) {
    default:
    case 0:
	cp = varval(STRprompt);
	break;
    case 1:
	cp = varval(STRprompt2);
	break;
    case 2:
	cp = varval(STRprompt3);
	break;
    case 3:
	if (ocp != NULL) {
	    cp = ocp;
	    str = ostr;
	}
	else 
	    cp = varval(STRprompt);
	break;
    }

    if (promptno < 2) {
	ocp = cp;
	ostr = str;
    }

    xfree(Prompt);
    Prompt = NULL;
    Prompt = tprintf(FMT_PROMPT, cp, str, lclock, NULL);
    if (!editing) {
	for (cp = Prompt; *cp ; )
	    (void) putwraw(*cp++);
	SetAttributes(0);
	flush();
    }

    xfree(RPrompt);
    RPrompt = NULL;
    if (promptno == 0) {	/* determine rprompt if using main prompt */
	cp = varval(STRrprompt);
	RPrompt = tprintf(FMT_PROMPT, cp, NULL, lclock, NULL);
				/* if not editing, put rprompt after prompt */
	if (!editing && RPrompt[0] != '\0') {
	    for (cp = RPrompt; *cp ; )
		(void) putwraw(*cp++);
	    SetAttributes(0);
	    putraw(' ');
	    flush();
	}
    }
}
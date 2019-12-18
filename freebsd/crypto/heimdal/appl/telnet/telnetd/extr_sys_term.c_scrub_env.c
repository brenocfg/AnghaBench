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
 char** environ ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scrub_env(void)
{
    static const char *reject[] = {
	"TERMCAP=/",
	NULL
    };

    static const char *accept[] = {
	"XAUTH=", "XAUTHORITY=", "DISPLAY=",
	"TERM=",
	"EDITOR=",
	"PAGER=",
	"PRINTER=",
	"LOGNAME=",
	"POSIXLY_CORRECT=",
	"TERMCAP=",
	NULL
    };

    char **cpp, **cpp2;
    const char **p;

    for (cpp2 = cpp = environ; *cpp; cpp++) {
	int reject_it = 0;

	for(p = reject; *p; p++)
	    if(strncmp(*cpp, *p, strlen(*p)) == 0) {
		reject_it = 1;
		break;
	    }
	if (reject_it)
	    continue;

	for(p = accept; *p; p++)
	    if(strncmp(*cpp, *p, strlen(*p)) == 0)
		break;
	if(*p != NULL)
	    *cpp2++ = *cpp;
    }
    *cpp2 = NULL;
}
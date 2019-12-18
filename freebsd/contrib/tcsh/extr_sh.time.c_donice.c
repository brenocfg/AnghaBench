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
struct command {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_SYSTEM ; 
 int /*<<< orphan*/  PRIO_PROCESS ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 scalar_t__ any (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int getn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nice (int) ; 
 int setpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

void
donice(Char **v, struct command *c)
{
    Char *cp;
    int	    nval = 0;

    USE(c);
    v++, cp = *v++;
    if (cp == 0)
	nval = 4;
    else if (*v	== 0 &&	any("+-", cp[0]))
	nval = getn(cp);
#if defined(HAVE_SETPRIORITY) && defined(PRIO_PROCESS)
    if (setpriority(PRIO_PROCESS, 0, nval) == -1 && errno)
	stderror(ERR_SYSTEM, "setpriority", strerror(errno));
#else /* !HAVE_SETPRIORITY || !PRIO_PROCESS */
    (void) nice(nval);
#endif /* HAVE_SETPRIORITY && PRIO_PROCESS */
}
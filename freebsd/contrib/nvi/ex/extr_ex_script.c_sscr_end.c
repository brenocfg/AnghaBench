#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* script; } ;
struct TYPE_8__ {int sh_master; int sh_slave; struct TYPE_8__* sh_prompt; scalar_t__ sh_pid; } ;
typedef  TYPE_1__ SCRIPT ;
typedef  TYPE_2__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  F_CLR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_SCRIPT ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_wait (TYPE_2__*,long,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscr_check (TYPE_2__*) ; 

int
sscr_end(SCR *sp)
{
	SCRIPT *sc;

	if ((sc = sp->script) == NULL)
		return (0);

	/* Turn off the script flags. */
	F_CLR(sp, SC_SCRIPT);
	sscr_check(sp);

	/* Close down the parent's file descriptors. */
	if (sc->sh_master != -1)
	    (void)close(sc->sh_master);
	if (sc->sh_slave != -1)
	    (void)close(sc->sh_slave);

	/* This should have killed the child. */
	(void)proc_wait(sp, (long)sc->sh_pid, "script-shell", 0, 0);

	/* Free memory. */
	free(sc->sh_prompt);
	free(sc);
	sp->script = NULL;

	return (0);
}
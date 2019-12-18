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
typedef  int time_t ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int /*<<< orphan*/ * STRNULL ; 
 int /*<<< orphan*/ * STRperiodic ; 
 int /*<<< orphan*/  STRtperiod ; 
 int /*<<< orphan*/ * STRunalias ; 
 scalar_t__ adrof1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aliases ; 
 int /*<<< orphan*/  aliasrun (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disabled_cleanup ; 
 int getn (int /*<<< orphan*/ *) ; 
 int periodic_active ; 
 int /*<<< orphan*/  pintr_disabled ; 
 int t_period ; 
 int /*<<< orphan*/  time (int*) ; 
 int /*<<< orphan*/ * varval (int /*<<< orphan*/ ) ; 
 scalar_t__ whyles ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 

void
period_cmd(void)
{
    Char *vp;
    time_t  t, interval;

    if (whyles)
	return;
    pintr_disabled++;
    cleanup_push(&pintr_disabled, disabled_cleanup);
    if (periodic_active) {	/* an error must have been caught */
	aliasrun(2, STRunalias, STRperiodic);
	xprintf("%s", CGETS(22, 6, "Faulty alias 'periodic' removed.\n"));
	goto leave;
    }
    periodic_active = 1;
    if (!whyles && adrof1(STRperiodic, &aliases)) {
	vp = varval(STRtperiod);
	if (vp == STRNULL) {
	    aliasrun(1, STRperiodic, NULL);
	    goto leave;
	}
	interval = getn(vp);
	(void) time(&t);
	if (t - t_period >= interval * 60) {
	    t_period = t;
	    aliasrun(1, STRperiodic, NULL);
	}
    }
leave:
    periodic_active = 0;
    cleanup_until(&pintr_disabled);
}
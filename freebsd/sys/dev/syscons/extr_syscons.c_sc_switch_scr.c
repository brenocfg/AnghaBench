#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_17__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct tty {int dummy; } ;
struct proc {int dummy; } ;
struct TYPE_23__ {scalar_t__ mode; } ;
struct TYPE_25__ {int status; scalar_t__ index; TYPE_1__ smode; int /*<<< orphan*/  pid; struct proc* proc; int /*<<< orphan*/  bell_duration; int /*<<< orphan*/  bell_pitch; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_26__ {int flags; scalar_t__ first_vty; scalar_t__ vtys; scalar_t__ unit; scalar_t__ switch_in_progress; TYPE_3__* cur_scp; TYPE_3__* old_scp; TYPE_3__* new_scp; scalar_t__ delayed_next_scr; scalar_t__ blink_in_progress; scalar_t__ write_in_progress; } ;
typedef  TYPE_4__ sc_softc_t ;
struct TYPE_24__ {scalar_t__ mode; } ;
struct TYPE_22__ {TYPE_2__ smode; } ;
struct TYPE_21__ {int /*<<< orphan*/  bell_pitch; } ;
struct TYPE_20__ {scalar_t__ index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BELL_DURATION ; 
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ISGRAPHSC (TYPE_3__*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 struct tty* SC_DEV (TYPE_4__*,scalar_t__) ; 
 int SC_SCRN_BLANKED ; 
 int SC_SCRN_VTYLOCK ; 
 TYPE_17__* SC_STAT (struct tty*) ; 
 int SWITCH_WAIT_ACQ ; 
 int SWITCH_WAIT_REL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VTY_WCHAN (TYPE_4__*,scalar_t__) ; 
 scalar_t__ VT_AUTO ; 
 scalar_t__ VT_PROCESS ; 
 TYPE_15__ bios_value ; 
 int /*<<< orphan*/  cnavailable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exchange_scr (TYPE_4__*) ; 
 int /*<<< orphan*/  finish_vt_acq (TYPE_3__*) ; 
 int /*<<< orphan*/  finish_vt_rel (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ kdb_active ; 
 struct proc* pfind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_bell (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_10__* sc_console ; 
 scalar_t__ sc_console_unit ; 
 int /*<<< orphan*/  sc_consptr ; 
 TYPE_3__* sc_get_stat (struct tty*) ; 
 int /*<<< orphan*/  sc_touch_scrn_saver () ; 
 scalar_t__ signal_vt_acq (TYPE_3__*) ; 
 scalar_t__ signal_vt_rel (TYPE_3__*) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 
 scalar_t__ tty_opened_ns (struct tty*) ; 
 int /*<<< orphan*/  vt_proc_alive (TYPE_3__*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

int
sc_switch_scr(sc_softc_t *sc, u_int next_scr)
{
    scr_stat *cur_scp;
    struct tty *tp;
    struct proc *p;
    int s;

    DPRINTF(5, ("sc0: sc_switch_scr() %d ", next_scr + 1));

    if (sc->cur_scp == NULL)
	return (0);

    /* prevent switch if previously requested */
    if (sc->flags & SC_SCRN_VTYLOCK) {
	    sc_bell(sc->cur_scp, sc->cur_scp->bell_pitch,
		sc->cur_scp->bell_duration);
	    return EPERM;
    }

    /* delay switch if the screen is blanked or being updated */
    if ((sc->flags & SC_SCRN_BLANKED) || sc->write_in_progress
	|| sc->blink_in_progress) {
	sc->delayed_next_scr = next_scr + 1;
	sc_touch_scrn_saver();
	DPRINTF(5, ("switch delayed\n"));
	return 0;
    }
    sc->delayed_next_scr = 0;

    s = spltty();
    cur_scp = sc->cur_scp;

    /* we are in the middle of the vty switching process... */
    if (sc->switch_in_progress
	&& (cur_scp->smode.mode == VT_PROCESS)
	&& cur_scp->proc) {
	p = pfind(cur_scp->pid);
	if (cur_scp->proc != p) {
	    if (p)
		PROC_UNLOCK(p);
	    /* 
	     * The controlling process has died!!.  Do some clean up.
	     * NOTE:`cur_scp->proc' and `cur_scp->smode.mode' 
	     * are not reset here yet; they will be cleared later.
	     */
	    DPRINTF(5, ("cur_scp controlling process %d died, ",
	       cur_scp->pid));
	    if (cur_scp->status & SWITCH_WAIT_REL) {
		/*
		 * Force the previous switch to finish, but return now 
		 * with error.
		 */
		DPRINTF(5, ("reset WAIT_REL, "));
		finish_vt_rel(cur_scp, TRUE, &s);
		splx(s);
		DPRINTF(5, ("finishing previous switch\n"));
		return EINVAL;
	    } else if (cur_scp->status & SWITCH_WAIT_ACQ) {
		/* let's assume screen switch has been completed. */
		DPRINTF(5, ("reset WAIT_ACQ, "));
		finish_vt_acq(cur_scp);
	    } else {
		/* 
	 	 * We are in between screen release and acquisition, and
		 * reached here via scgetc() or scrn_timer() which has 
		 * interrupted exchange_scr(). Don't do anything stupid.
		 */
		DPRINTF(5, ("waiting nothing, "));
	    }
	} else {
	    if (p)
		PROC_UNLOCK(p);
	    /*
	     * The controlling process is alive, but not responding... 
	     * It is either buggy or it may be just taking time.
	     * The following code is a gross kludge to cope with this
	     * problem for which there is no clean solution. XXX
	     */
	    if (cur_scp->status & SWITCH_WAIT_REL) {
		switch (sc->switch_in_progress++) {
		case 1:
		    break;
		case 2:
		    DPRINTF(5, ("sending relsig again, "));
		    signal_vt_rel(cur_scp);
		    break;
		case 3:
		    break;
		case 4:
		default:
		    /*
		     * Act as if the controlling program returned
		     * VT_FALSE.
		     */
		    DPRINTF(5, ("force reset WAIT_REL, "));
		    finish_vt_rel(cur_scp, FALSE, &s);
		    splx(s);
		    DPRINTF(5, ("act as if VT_FALSE was seen\n"));
		    return EINVAL;
		}
	    } else if (cur_scp->status & SWITCH_WAIT_ACQ) {
		switch (sc->switch_in_progress++) {
		case 1:
		    break;
		case 2:
		    DPRINTF(5, ("sending acqsig again, "));
		    signal_vt_acq(cur_scp);
		    break;
		case 3:
		    break;
		case 4:
		default:
		     /* clear the flag and finish the previous switch */
		    DPRINTF(5, ("force reset WAIT_ACQ, "));
		    finish_vt_acq(cur_scp);
		    break;
		}
	    }
	}
    }

    /*
     * Return error if an invalid argument is given, or vty switch
     * is still in progress.
     */
    if ((next_scr < sc->first_vty) || (next_scr >= sc->first_vty + sc->vtys)
	|| sc->switch_in_progress) {
	splx(s);
	sc_bell(cur_scp, bios_value.bell_pitch, BELL_DURATION);
	DPRINTF(5, ("error 1\n"));
	return EINVAL;
    }

    /*
     * Don't allow switching away from the graphics mode vty
     * if the switch mode is VT_AUTO, unless the next vty is the same 
     * as the current or the current vty has been closed (but showing).
     */
    tp = SC_DEV(sc, cur_scp->index);
    if ((cur_scp->index != next_scr)
	&& tty_opened_ns(tp)
	&& (cur_scp->smode.mode == VT_AUTO)
	&& ISGRAPHSC(cur_scp)) {
	splx(s);
	sc_bell(cur_scp, bios_value.bell_pitch, BELL_DURATION);
	DPRINTF(5, ("error, graphics mode\n"));
	return EINVAL;
    }

    /*
     * Is the wanted vty open? Don't allow switching to a closed vty.
     * If we are in DDB, don't switch to a vty in the VT_PROCESS mode.
     * Note that we always allow the user to switch to the kernel 
     * console even if it is closed.
     */
    if ((sc_console == NULL) || (next_scr != sc_console->index)) {
	tp = SC_DEV(sc, next_scr);
	if (!tty_opened_ns(tp)) {
	    splx(s);
	    sc_bell(cur_scp, bios_value.bell_pitch, BELL_DURATION);
	    DPRINTF(5, ("error 2, requested vty isn't open!\n"));
	    return EINVAL;
	}
	if (kdb_active && SC_STAT(tp)->smode.mode == VT_PROCESS) {
	    splx(s);
	    DPRINTF(5, ("error 3, requested vty is in the VT_PROCESS mode\n"));
	    return EINVAL;
	}
    }

    /* this is the start of vty switching process... */
    ++sc->switch_in_progress;
    sc->old_scp = cur_scp;
    sc->new_scp = sc_get_stat(SC_DEV(sc, next_scr));
    if (sc->new_scp == sc->old_scp) {
	sc->switch_in_progress = 0;
	/*
	 * XXX wakeup() locks the scheduler lock which will hang if
	 * the lock is in an in-between state, e.g., when we stop at
	 * a breakpoint at fork_exit.  It has always been wrong to call
	 * wakeup() when the debugger is active.  In RELENG_4, wakeup()
	 * is supposed to be locked by splhigh(), but the debugger may
	 * be invoked at splhigh().
	 */
	if (!kdb_active)
	    wakeup(VTY_WCHAN(sc,next_scr));
	splx(s);
	DPRINTF(5, ("switch done (new == old)\n"));
	return 0;
    }

    /* has controlling process died? */
    vt_proc_alive(sc->old_scp);
    vt_proc_alive(sc->new_scp);

    /* wait for the controlling process to release the screen, if necessary */
    if (signal_vt_rel(sc->old_scp)) {
	splx(s);
	return 0;
    }

    /* go set up the new vty screen */
    splx(s);
    exchange_scr(sc);
    s = spltty();

    /* wake up processes waiting for this vty */
    if (!kdb_active)
	wakeup(VTY_WCHAN(sc,next_scr));

    /* wait for the controlling process to acknowledge, if necessary */
    if (signal_vt_acq(sc->cur_scp)) {
	splx(s);
	return 0;
    }

    sc->switch_in_progress = 0;
    if (sc->unit == sc_console_unit)
	cnavailable(sc_consptr,  TRUE);
    splx(s);
    DPRINTF(5, ("switch done\n"));

    return 0;
}
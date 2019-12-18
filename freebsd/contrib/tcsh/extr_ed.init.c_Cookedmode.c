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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_IO ; 
 int /*<<< orphan*/  SHTTY ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 scalar_t__ Tty_raw_mode ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_nt_cooked_mode () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  extty ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask_cleanup ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_setdisc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tty_setty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 

int
Cookedmode(void)
{				/* set tty in normal setup */
#ifdef WINNT_NATIVE
    do_nt_cooked_mode();
#else
    sigset_t set, oset;
    int res;

# ifdef _IBMR2
    tty_setdisc(SHTTY, EX_IO);
# endif /* _IBMR2 */

    if (!Tty_raw_mode)
	return (0);

    /* hold this for reseting tty */
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    (void)sigprocmask(SIG_BLOCK, &set, &oset);
    cleanup_push(&oset, sigprocmask_cleanup);
    res = tty_setty(SHTTY, &extty);
    cleanup_until(&oset);
    if (res == -1) {
# ifdef DEBUG_TTY
	xprintf("Cookedmode: tty_setty: %s\n", strerror(errno));
# endif /* DEBUG_TTY */
	return -1;
    }
#endif /* WINNT_NATIVE */

    Tty_raw_mode = 0;
    return (0);
}
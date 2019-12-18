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
struct recvbuf {int /*<<< orphan*/  dstadr; int /*<<< orphan*/  recv_srcadr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CERR_BADASSOC ; 
 int RES_LPTRAP ; 
 int TRAP_TYPE_NONPRIO ; 
 int TRAP_TYPE_PRIO ; 
 int /*<<< orphan*/  ctl_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_flushpkt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctlclrtrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
unset_trap(
	struct recvbuf *rbufp,
	int restrict_mask
	)
{
	int traptype;

	/*
	 * We don't prevent anyone from removing his own trap unless the
	 * trap is configured. Note we also must be aware of the
	 * possibility that restriction flags were changed since this
	 * guy last set his trap. Set the trap type based on this.
	 */
	traptype = TRAP_TYPE_PRIO;
	if (restrict_mask & RES_LPTRAP)
		traptype = TRAP_TYPE_NONPRIO;

	/*
	 * Call ctlclrtrap() to clear this out.
	 */
	if (!ctlclrtrap(&rbufp->recv_srcadr, rbufp->dstadr, traptype))
		ctl_error(CERR_BADASSOC);
	ctl_flushpkt(0);
}
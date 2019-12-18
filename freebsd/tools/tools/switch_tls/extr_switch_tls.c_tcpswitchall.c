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
struct xinpcb {scalar_t__ inp_gencnt; int /*<<< orphan*/  inp_inc; } ;
struct xtcpcb {scalar_t__ t_state; int /*<<< orphan*/  xt_stack; struct xinpcb xt_inp; } ;
struct xinpgen {int xig_len; scalar_t__ xig_gen; } ;

/* Variables and functions */
 scalar_t__ TCPS_LISTEN ; 
 int /*<<< orphan*/  TCP_FUNCTION_NAME_LEN_MAX ; 
 struct xinpgen* XINP_NEXT (struct xinpgen*) ; 
 int /*<<< orphan*/  free (struct xinpgen*) ; 
 struct xinpgen* getxpcblist (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpswitchconn (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
tcpswitchall(const char *stack, int mode)
{
	struct xinpgen *head, *xinp;
	struct xtcpcb *xtp;
	struct xinpcb *xip;
	bool ok;

	ok = true;

	head = getxpcblist("net.inet.tcp.pcblist");

#define	XINP_NEXT(xinp)							\
	((struct xinpgen *)(uintptr_t)((uintptr_t)(xinp) + (xinp)->xig_len))

	for (xinp = XINP_NEXT(head); xinp->xig_len > sizeof *xinp;
	    xinp = XINP_NEXT(xinp)) {
		xtp = (struct xtcpcb *)xinp;
		xip = &xtp->xt_inp;

		/*
		 * XXX
		 * Check protocol, support just v4 or v6, etc.
		 */

		/* Ignore PCBs which were freed during copyout.  */
		if (xip->inp_gencnt > head->xig_gen)
			continue;

		/* Skip listening sockets.  */
		if (xtp->t_state == TCPS_LISTEN)
			continue;

		/* If requested, skip sockets not having the requested stack. */
		if (stack[0] != '\0' &&
		    strncmp(xtp->xt_stack, stack, TCP_FUNCTION_NAME_LEN_MAX))
			continue;

		if (!tcpswitchconn(&xip->inp_inc, mode))
			ok = false;
	}
	free(head);

	return (ok);
}
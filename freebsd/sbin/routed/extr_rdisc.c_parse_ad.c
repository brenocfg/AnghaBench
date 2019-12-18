#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
struct msg_limit {int dummy; } ;
struct interface {int int_state; int /*<<< orphan*/  int_rdisc_cnt; int /*<<< orphan*/  int_mask; int /*<<< orphan*/  int_net; } ;
struct dr {scalar_t__ dr_gate; scalar_t__ dr_ts; scalar_t__ dr_pref; scalar_t__ dr_recv_pref; scalar_t__ dr_life; struct interface* dr_ifp; } ;
typedef  scalar_t__ naddr ;
typedef  scalar_t__ n_long ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int IS_SICK ; 
 size_t MAX_ADS ; 
 int /*<<< orphan*/  MAX_SOLICITATIONS ; 
 scalar_t__ MinMaxAdvertiseInterval ; 
 scalar_t__ PREF (scalar_t__,struct interface*) ; 
 scalar_t__ RIP_DEFAULT ; 
 scalar_t__ UNSIGN_PREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_dst (scalar_t__) ; 
 struct dr* drs ; 
 int /*<<< orphan*/ * ifwithaddr (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msglim (struct msg_limit*,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  naddr_ntoa (scalar_t__) ; 
 TYPE_1__ now ; 
 int /*<<< orphan*/  ntohl (scalar_t__) ; 
 int /*<<< orphan*/  on_net (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_pkt (char*) ; 

__attribute__((used)) static void
parse_ad(naddr from,
	 naddr gate,
	 n_long pref,			/* signed and in network order */
	 u_short life,			/* in host byte order */
	 struct interface *ifp)
{
	static struct msg_limit bad_gate;
	struct dr *drp, *new_drp;


	if (gate == RIP_DEFAULT
	    || !check_dst(gate)) {
		msglim(&bad_gate, from,"router %s advertising bad gateway %s",
		       naddr_ntoa(from),
		       naddr_ntoa(gate));
		return;
	}

	/* ignore pointers to ourself and routes via unreachable networks
	 */
	if (ifwithaddr(gate, 1, 0) != NULL) {
		trace_pkt("    discard Router Discovery Ad pointing at us");
		return;
	}
	if (!on_net(gate, ifp->int_net, ifp->int_mask)) {
		trace_pkt("    discard Router Discovery Ad"
			  " toward unreachable net");
		return;
	}

	/* Convert preference to an unsigned value
	 * and later bias it by the metric of the interface.
	 */
	pref = UNSIGN_PREF(ntohl(pref));

	if (pref == 0 || life < MinMaxAdvertiseInterval) {
		pref = 0;
		life = 0;
	}

	for (new_drp = NULL, drp = drs; drp < &drs[MAX_ADS]; drp++) {
		/* accept new info for a familiar entry
		 */
		if (drp->dr_gate == gate) {
			new_drp = drp;
			break;
		}

		if (life == 0)
			continue;	/* do not worry about dead ads */

		if (drp->dr_ts == 0) {
			new_drp = drp;	/* use unused entry */

		} else if (new_drp == NULL) {
			/* look for an entry worse than the new one to
			 * reuse.
			 */
			if ((!(ifp->int_state & IS_SICK)
			     && (drp->dr_ifp->int_state & IS_SICK))
			    || (pref > drp->dr_pref
				&& !((ifp->int_state ^ drp->dr_ifp->int_state)
				     & IS_SICK)))
				new_drp = drp;

		} else if (new_drp->dr_ts != 0) {
			/* look for the least valuable entry to reuse
			 */
			if ((!(new_drp->dr_ifp->int_state & IS_SICK)
			     && (drp->dr_ifp->int_state & IS_SICK))
			    || (new_drp->dr_pref > drp->dr_pref
				&& !((new_drp->dr_ifp->int_state
				      ^ drp->dr_ifp->int_state)
				     & IS_SICK)))
				new_drp = drp;
		}
	}

	/* forget it if all of the current entries are better */
	if (new_drp == NULL)
		return;

	new_drp->dr_ifp = ifp;
	new_drp->dr_gate = gate;
	new_drp->dr_ts = now.tv_sec;
	new_drp->dr_life = life;
	new_drp->dr_recv_pref = pref;
	/* bias functional preference by metric of the interface */
	new_drp->dr_pref = PREF(pref,ifp);

	/* after hearing a good advertisement, stop asking
	 */
	if (!(ifp->int_state & IS_SICK))
		ifp->int_rdisc_cnt = MAX_SOLICITATIONS;
}
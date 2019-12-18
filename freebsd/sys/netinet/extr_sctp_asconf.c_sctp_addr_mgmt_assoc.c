#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_15__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_7__ sin_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  ipv4_local_scope; int /*<<< orphan*/  site_scope; int /*<<< orphan*/  local_scope; } ;
struct TYPE_13__ {int /*<<< orphan*/  primary_destination; scalar_t__ asconf_supported; TYPE_4__ scope; } ;
struct sctp_tcb {TYPE_5__ asoc; } ;
struct TYPE_9__ {int /*<<< orphan*/  inp_cred; } ;
struct TYPE_10__ {TYPE_1__ inp; } ;
struct sctp_inpcb {int sctp_flags; TYPE_2__ ip_inp; } ;
struct TYPE_14__ {int sa_family; } ;
struct TYPE_11__ {struct sockaddr_in sin; TYPE_6__ sa; struct sockaddr_in6 sin6; } ;
struct sctp_ifa {int localifa_flags; TYPE_3__ address; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IN4_ISPRIVATE_ADDRESS (TYPE_7__*) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_SITELOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int SCTP_ADDR_IFA_UNUSEABLE ; 
 scalar_t__ SCTP_GET_STATE (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_IPV6_V6ONLY (struct sctp_inpcb*) ; 
 int SCTP_PCB_FLAGS_BOUNDALL ; 
 int SCTP_PCB_FLAGS_BOUND_V6 ; 
 int /*<<< orphan*/  SCTP_PCB_FLAGS_DO_ASCONF ; 
 scalar_t__ SCTP_STATE_OPEN ; 
 scalar_t__ SCTP_STATE_SHUTDOWN_RECEIVED ; 
 int /*<<< orphan*/  SCTP_TIMER_TYPE_ASCONF ; 
 int /*<<< orphan*/  prison_check_ip4 (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  prison_check_ip6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_add_local_addr_restricted (struct sctp_tcb*,struct sctp_ifa*) ; 
 int sctp_asconf_queue_add (struct sctp_tcb*,struct sctp_ifa*,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_is_feature_off (struct sctp_inpcb*,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_is_feature_on (struct sctp_inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_is_scopeid_in_nets (struct sctp_tcb*,TYPE_6__*) ; 
 int /*<<< orphan*/  sctp_send_asconf (struct sctp_tcb*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sctp_timer_start (int /*<<< orphan*/ ,struct sctp_inpcb*,struct sctp_tcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sctp_addr_mgmt_assoc(struct sctp_inpcb *inp, struct sctp_tcb *stcb,
    struct sctp_ifa *ifa, uint16_t type, int addr_locked)
{
	int status;

	if ((inp->sctp_flags & SCTP_PCB_FLAGS_BOUNDALL) == 0 ||
	    sctp_is_feature_off(inp, SCTP_PCB_FLAGS_DO_ASCONF)) {
		/* subset bound, no ASCONF allowed case, so ignore */
		return;
	}
	/*
	 * note: we know this is not the subset bound, no ASCONF case eg.
	 * this is boundall or subset bound w/ASCONF allowed
	 */

	/* first, make sure that the address is IPv4 or IPv6 and not jailed */
	switch (ifa->address.sa.sa_family) {
#ifdef INET6
	case AF_INET6:
		if (prison_check_ip6(inp->ip_inp.inp.inp_cred,
		    &ifa->address.sin6.sin6_addr) != 0) {
			return;
		}
		break;
#endif
#ifdef INET
	case AF_INET:
		if (prison_check_ip4(inp->ip_inp.inp.inp_cred,
		    &ifa->address.sin.sin_addr) != 0) {
			return;
		}
		break;
#endif
	default:
		return;
	}
#ifdef INET6
	/* make sure we're "allowed" to add this type of addr */
	if (ifa->address.sa.sa_family == AF_INET6) {
		/* invalid if we're not a v6 endpoint */
		if ((inp->sctp_flags & SCTP_PCB_FLAGS_BOUND_V6) == 0)
			return;
		/* is the v6 addr really valid ? */
		if (ifa->localifa_flags & SCTP_ADDR_IFA_UNUSEABLE) {
			return;
		}
	}
#endif
	/* put this address on the "pending/do not use yet" list */
	sctp_add_local_addr_restricted(stcb, ifa);
	/*
	 * check address scope if address is out of scope, don't queue
	 * anything... note: this would leave the address on both inp and
	 * asoc lists
	 */
	switch (ifa->address.sa.sa_family) {
#ifdef INET6
	case AF_INET6:
		{
			struct sockaddr_in6 *sin6;

			sin6 = &ifa->address.sin6;
			if (IN6_IS_ADDR_UNSPECIFIED(&sin6->sin6_addr)) {
				/* we skip unspecifed addresses */
				return;
			}
			if (IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr)) {
				if (stcb->asoc.scope.local_scope == 0) {
					return;
				}
				/* is it the right link local scope? */
				if (sctp_is_scopeid_in_nets(stcb, &ifa->address.sa) == 0) {
					return;
				}
			}
			if (stcb->asoc.scope.site_scope == 0 &&
			    IN6_IS_ADDR_SITELOCAL(&sin6->sin6_addr)) {
				return;
			}
			break;
		}
#endif
#ifdef INET
	case AF_INET:
		{
			struct sockaddr_in *sin;

			/* invalid if we are a v6 only endpoint */
			if ((inp->sctp_flags & SCTP_PCB_FLAGS_BOUND_V6) &&
			    SCTP_IPV6_V6ONLY(inp))
				return;

			sin = &ifa->address.sin;
			if (sin->sin_addr.s_addr == 0) {
				/* we skip unspecifed addresses */
				return;
			}
			if (stcb->asoc.scope.ipv4_local_scope == 0 &&
			    IN4_ISPRIVATE_ADDRESS(&sin->sin_addr)) {
				return;
			}
			break;
		}
#endif
	default:
		/* else, not AF_INET or AF_INET6, so skip */
		return;
	}

	/* queue an asconf for this address add/delete */
	if (sctp_is_feature_on(inp, SCTP_PCB_FLAGS_DO_ASCONF)) {
		/* does the peer do asconf? */
		if (stcb->asoc.asconf_supported) {
			/* queue an asconf for this addr */
			status = sctp_asconf_queue_add(stcb, ifa, type);

			/*
			 * if queued ok, and in the open state, send out the
			 * ASCONF.  If in the non-open state, these will be
			 * sent when the state goes open.
			 */
			if (status == 0 &&
			    ((SCTP_GET_STATE(stcb) == SCTP_STATE_OPEN) ||
			    (SCTP_GET_STATE(stcb) == SCTP_STATE_SHUTDOWN_RECEIVED))) {
#ifdef SCTP_TIMER_BASED_ASCONF
				sctp_timer_start(SCTP_TIMER_TYPE_ASCONF, inp,
				    stcb, stcb->asoc.primary_destination);
#else
				sctp_send_asconf(stcb, NULL, addr_locked);
#endif
			}
		}
	}
}
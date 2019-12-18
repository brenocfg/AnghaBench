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
typedef  int /*<<< orphan*/  uint32_t ;
struct socket {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {scalar_t__ sin_port; } ;
struct sockaddr {scalar_t__ sa_family; int sa_len; } ;
struct sctp_inpcb {int sctp_flags; scalar_t__ sctp_lport; } ;
typedef  scalar_t__ sctp_assoc_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EADDRINUSE ; 
 int EINVAL ; 
 scalar_t__ IN6_IS_ADDR_V4MAPPED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCTP_ADD_IP_ADDRESS ; 
 int /*<<< orphan*/  SCTP_FROM_SCTPUTIL ; 
 int /*<<< orphan*/  SCTP_INP_DECR_REF (struct sctp_inpcb*) ; 
 scalar_t__ SCTP_IPV6_V6ONLY (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_LTRACE_ERR_RET (struct sctp_inpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int SCTP_PCB_FLAGS_BOUNDALL ; 
 int SCTP_PCB_FLAGS_BOUND_V6 ; 
 int SCTP_PCB_FLAGS_UNBOUND ; 
 int /*<<< orphan*/  in6_sin6_2_sin (struct sockaddr_in*,struct sockaddr_in6*) ; 
 int sctp_addr_mgmt_ep_sa (struct sctp_inpcb*,struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sctp_inpcb_bind (struct socket*,struct sockaddr*,int /*<<< orphan*/ *,void*) ; 
 struct sctp_inpcb* sctp_pcb_findep (struct sockaddr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sctp_bindx_add_address(struct socket *so, struct sctp_inpcb *inp,
    struct sockaddr *sa, sctp_assoc_t assoc_id,
    uint32_t vrf_id, int *error, void *p)
{
	struct sockaddr *addr_touse;
#if defined(INET) && defined(INET6)
	struct sockaddr_in sin;
#endif

	/* see if we're bound all already! */
	if (inp->sctp_flags & SCTP_PCB_FLAGS_BOUNDALL) {
		SCTP_LTRACE_ERR_RET(inp, NULL, NULL, SCTP_FROM_SCTPUTIL, EINVAL);
		*error = EINVAL;
		return;
	}
	addr_touse = sa;
#ifdef INET6
	if (sa->sa_family == AF_INET6) {
#ifdef INET
		struct sockaddr_in6 *sin6;

#endif
		if (sa->sa_len != sizeof(struct sockaddr_in6)) {
			SCTP_LTRACE_ERR_RET(inp, NULL, NULL, SCTP_FROM_SCTPUTIL, EINVAL);
			*error = EINVAL;
			return;
		}
		if ((inp->sctp_flags & SCTP_PCB_FLAGS_BOUND_V6) == 0) {
			/* can only bind v6 on PF_INET6 sockets */
			SCTP_LTRACE_ERR_RET(inp, NULL, NULL, SCTP_FROM_SCTPUTIL, EINVAL);
			*error = EINVAL;
			return;
		}
#ifdef INET
		sin6 = (struct sockaddr_in6 *)addr_touse;
		if (IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr)) {
			if ((inp->sctp_flags & SCTP_PCB_FLAGS_BOUND_V6) &&
			    SCTP_IPV6_V6ONLY(inp)) {
				/* can't bind v4-mapped on PF_INET sockets */
				SCTP_LTRACE_ERR_RET(inp, NULL, NULL, SCTP_FROM_SCTPUTIL, EINVAL);
				*error = EINVAL;
				return;
			}
			in6_sin6_2_sin(&sin, sin6);
			addr_touse = (struct sockaddr *)&sin;
		}
#endif
	}
#endif
#ifdef INET
	if (sa->sa_family == AF_INET) {
		if (sa->sa_len != sizeof(struct sockaddr_in)) {
			SCTP_LTRACE_ERR_RET(inp, NULL, NULL, SCTP_FROM_SCTPUTIL, EINVAL);
			*error = EINVAL;
			return;
		}
		if ((inp->sctp_flags & SCTP_PCB_FLAGS_BOUND_V6) &&
		    SCTP_IPV6_V6ONLY(inp)) {
			/* can't bind v4 on PF_INET sockets */
			SCTP_LTRACE_ERR_RET(inp, NULL, NULL, SCTP_FROM_SCTPUTIL, EINVAL);
			*error = EINVAL;
			return;
		}
	}
#endif
	if (inp->sctp_flags & SCTP_PCB_FLAGS_UNBOUND) {
		if (p == NULL) {
			/* Can't get proc for Net/Open BSD */
			SCTP_LTRACE_ERR_RET(inp, NULL, NULL, SCTP_FROM_SCTPUTIL, EINVAL);
			*error = EINVAL;
			return;
		}
		*error = sctp_inpcb_bind(so, addr_touse, NULL, p);
		return;
	}
	/*
	 * No locks required here since bind and mgmt_ep_sa all do their own
	 * locking. If we do something for the FIX: below we may need to
	 * lock in that case.
	 */
	if (assoc_id == 0) {
		/* add the address */
		struct sctp_inpcb *lep;
		struct sockaddr_in *lsin = (struct sockaddr_in *)addr_touse;

		/* validate the incoming port */
		if ((lsin->sin_port != 0) &&
		    (lsin->sin_port != inp->sctp_lport)) {
			SCTP_LTRACE_ERR_RET(inp, NULL, NULL, SCTP_FROM_SCTPUTIL, EINVAL);
			*error = EINVAL;
			return;
		} else {
			/* user specified 0 port, set it to existing port */
			lsin->sin_port = inp->sctp_lport;
		}

		lep = sctp_pcb_findep(addr_touse, 1, 0, vrf_id);
		if (lep != NULL) {
			/*
			 * We must decrement the refcount since we have the
			 * ep already and are binding. No remove going on
			 * here.
			 */
			SCTP_INP_DECR_REF(lep);
		}
		if (lep == inp) {
			/* already bound to it.. ok */
			return;
		} else if (lep == NULL) {
			((struct sockaddr_in *)addr_touse)->sin_port = 0;
			*error = sctp_addr_mgmt_ep_sa(inp, addr_touse,
			    SCTP_ADD_IP_ADDRESS,
			    vrf_id, NULL);
		} else {
			*error = EADDRINUSE;
		}
		if (*error)
			return;
	} else {
		/*
		 * FIX: decide whether we allow assoc based bindx
		 */
	}
}
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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; int sa_len; } ;
struct sctp_inpcb {int sctp_flags; } ;
typedef  scalar_t__ sctp_assoc_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 scalar_t__ IN6_IS_ADDR_V4MAPPED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCTP_DEL_IP_ADDRESS ; 
 int /*<<< orphan*/  SCTP_FROM_SCTPUTIL ; 
 scalar_t__ SCTP_IPV6_V6ONLY (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_LTRACE_ERR_RET (struct sctp_inpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int SCTP_PCB_FLAGS_BOUNDALL ; 
 int SCTP_PCB_FLAGS_BOUND_V6 ; 
 int /*<<< orphan*/  in6_sin6_2_sin (struct sockaddr_in*,struct sockaddr_in6*) ; 
 int sctp_addr_mgmt_ep_sa (struct sctp_inpcb*,struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
sctp_bindx_delete_address(struct sctp_inpcb *inp,
    struct sockaddr *sa, sctp_assoc_t assoc_id,
    uint32_t vrf_id, int *error)
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
				/* can't bind mapped-v4 on PF_INET sockets */
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
	/*
	 * No lock required mgmt_ep_sa does its own locking. If the FIX:
	 * below is ever changed we may need to lock before calling
	 * association level binding.
	 */
	if (assoc_id == 0) {
		/* delete the address */
		*error = sctp_addr_mgmt_ep_sa(inp, addr_touse,
		    SCTP_DEL_IP_ADDRESS,
		    vrf_id, NULL);
	} else {
		/*
		 * FIX: decide whether we allow assoc based bindx
		 */
	}
}
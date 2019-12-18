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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int sa_family; unsigned int sa_len; } ;
struct sctp_tcb {int dummy; } ;
struct sctp_inpcb {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EALREADY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IN6_IS_ADDR_V4MAPPED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCTP_INP_DECR_REF (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_INP_INCR_REF (struct sctp_inpcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_UNLOCK (struct sctp_tcb*) ; 
 struct sctp_tcb* sctp_findassociation_ep_addr (struct sctp_inpcb**,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
sctp_connectx_helper_find(struct sctp_inpcb *inp, struct sockaddr *addr,
    unsigned int totaddr,
    unsigned int *num_v4, unsigned int *num_v6,
    unsigned int limit)
{
	struct sockaddr *sa;
	struct sctp_tcb *stcb;
	unsigned int incr, at, i;

	at = 0;
	sa = addr;
	*num_v6 = *num_v4 = 0;
	/* account and validate addresses */
	if (totaddr == 0) {
		return (EINVAL);
	}
	for (i = 0; i < totaddr; i++) {
		if (at + sizeof(struct sockaddr) > limit) {
			return (EINVAL);
		}
		switch (sa->sa_family) {
#ifdef INET
		case AF_INET:
			incr = (unsigned int)sizeof(struct sockaddr_in);
			if (sa->sa_len != incr) {
				return (EINVAL);
			}
			(*num_v4) += 1;
			break;
#endif
#ifdef INET6
		case AF_INET6:
			{
				struct sockaddr_in6 *sin6;

				sin6 = (struct sockaddr_in6 *)sa;
				if (IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr)) {
					/* Must be non-mapped for connectx */
					return (EINVAL);
				}
				incr = (unsigned int)sizeof(struct sockaddr_in6);
				if (sa->sa_len != incr) {
					return (EINVAL);
				}
				(*num_v6) += 1;
				break;
			}
#endif
		default:
			return (EINVAL);
		}
		if ((at + incr) > limit) {
			return (EINVAL);
		}
		SCTP_INP_INCR_REF(inp);
		stcb = sctp_findassociation_ep_addr(&inp, sa, NULL, NULL, NULL);
		if (stcb != NULL) {
			SCTP_TCB_UNLOCK(stcb);
			return (EALREADY);
		} else {
			SCTP_INP_DECR_REF(inp);
		}
		at += incr;
		sa = (struct sockaddr *)((caddr_t)sa + incr);
	}
	return (0);
}
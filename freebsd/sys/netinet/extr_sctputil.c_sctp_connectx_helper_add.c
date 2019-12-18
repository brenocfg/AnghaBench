#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;
struct sctp_tcb {TYPE_2__ asoc; struct sctp_inpcb* sctp_ep; } ;
struct sctp_inpcb {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  IN6_IS_ADDR_MULTICAST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IN6_IS_ADDR_UNSPECIFIED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INADDR_BROADCAST ; 
 int /*<<< orphan*/  IN_MULTICAST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_ADDR_IS_CONFIRMED ; 
 int /*<<< orphan*/  SCTP_DONOT_SETSCOPE ; 
 scalar_t__ SCTP_FROM_SCTPUTIL ; 
 scalar_t__ SCTP_LOC_10 ; 
 scalar_t__ SCTP_LOC_7 ; 
 scalar_t__ SCTP_LOC_8 ; 
 scalar_t__ SCTP_LOC_9 ; 
 int /*<<< orphan*/  SCTP_LTRACE_ERR_RET (int /*<<< orphan*/ *,struct sctp_tcb*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  SCTP_NORMAL_PROC ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_add_remote_addr (struct sctp_tcb*,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_free_assoc (struct sctp_inpcb*,struct sctp_tcb*,int /*<<< orphan*/ ,scalar_t__) ; 

int
sctp_connectx_helper_add(struct sctp_tcb *stcb, struct sockaddr *addr,
    int totaddr, int *error)
{
	int added = 0;
	int i;
	struct sctp_inpcb *inp;
	struct sockaddr *sa;
	size_t incr = 0;
#ifdef INET
	struct sockaddr_in *sin;
#endif
#ifdef INET6
	struct sockaddr_in6 *sin6;
#endif

	sa = addr;
	inp = stcb->sctp_ep;
	*error = 0;
	for (i = 0; i < totaddr; i++) {
		switch (sa->sa_family) {
#ifdef INET
		case AF_INET:
			incr = sizeof(struct sockaddr_in);
			sin = (struct sockaddr_in *)sa;
			if ((sin->sin_addr.s_addr == INADDR_ANY) ||
			    (sin->sin_addr.s_addr == INADDR_BROADCAST) ||
			    IN_MULTICAST(ntohl(sin->sin_addr.s_addr))) {
				SCTP_LTRACE_ERR_RET(NULL, stcb, NULL, SCTP_FROM_SCTPUTIL, EINVAL);
				(void)sctp_free_assoc(inp, stcb, SCTP_NORMAL_PROC,
				    SCTP_FROM_SCTPUTIL + SCTP_LOC_7);
				*error = EINVAL;
				goto out_now;
			}
			if (sctp_add_remote_addr(stcb, sa, NULL, stcb->asoc.port,
			    SCTP_DONOT_SETSCOPE,
			    SCTP_ADDR_IS_CONFIRMED)) {
				/* assoc gone no un-lock */
				SCTP_LTRACE_ERR_RET(NULL, stcb, NULL, SCTP_FROM_SCTPUTIL, ENOBUFS);
				(void)sctp_free_assoc(inp, stcb, SCTP_NORMAL_PROC,
				    SCTP_FROM_SCTPUTIL + SCTP_LOC_8);
				*error = ENOBUFS;
				goto out_now;
			}
			added++;
			break;
#endif
#ifdef INET6
		case AF_INET6:
			incr = sizeof(struct sockaddr_in6);
			sin6 = (struct sockaddr_in6 *)sa;
			if (IN6_IS_ADDR_UNSPECIFIED(&sin6->sin6_addr) ||
			    IN6_IS_ADDR_MULTICAST(&sin6->sin6_addr)) {
				SCTP_LTRACE_ERR_RET(NULL, stcb, NULL, SCTP_FROM_SCTPUTIL, EINVAL);
				(void)sctp_free_assoc(inp, stcb, SCTP_NORMAL_PROC,
				    SCTP_FROM_SCTPUTIL + SCTP_LOC_9);
				*error = EINVAL;
				goto out_now;
			}
			if (sctp_add_remote_addr(stcb, sa, NULL, stcb->asoc.port,
			    SCTP_DONOT_SETSCOPE,
			    SCTP_ADDR_IS_CONFIRMED)) {
				/* assoc gone no un-lock */
				SCTP_LTRACE_ERR_RET(NULL, stcb, NULL, SCTP_FROM_SCTPUTIL, ENOBUFS);
				(void)sctp_free_assoc(inp, stcb, SCTP_NORMAL_PROC,
				    SCTP_FROM_SCTPUTIL + SCTP_LOC_10);
				*error = ENOBUFS;
				goto out_now;
			}
			added++;
			break;
#endif
		default:
			break;
		}
		sa = (struct sockaddr *)((caddr_t)sa + incr);
	}
out_now:
	return (added);
}
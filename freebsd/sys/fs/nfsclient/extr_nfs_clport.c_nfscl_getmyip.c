#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct nhop4_extended {struct in_addr nh_src; } ;
struct TYPE_7__ {int /*<<< orphan*/  nr_cred; } ;
struct nfsmount {TYPE_3__ nm_sockreq; TYPE_2__* nm_nam; } ;
struct in6_addr {int dummy; } ;
struct TYPE_8__ {TYPE_1__* td_proc; } ;
struct TYPE_6__ {scalar_t__ sa_family; } ;
struct TYPE_5__ {int p_fibnum; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CRED_TO_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ IN6_IS_ADDR_LOOPBACK (struct in6_addr*) ; 
 scalar_t__ IN_LOOPBACK (int /*<<< orphan*/ ) ; 
 TYPE_4__* curthread ; 
 int fib4_lookup_nh_ext (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nhop4_extended*) ; 
 int in6_selectsrc_addr (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

u_int8_t *
nfscl_getmyip(struct nfsmount *nmp, struct in6_addr *paddr, int *isinet6p)
{
#if defined(INET6) || defined(INET)
	int error, fibnum;

	fibnum = curthread->td_proc->p_fibnum;
#endif
#ifdef INET
	if (nmp->nm_nam->sa_family == AF_INET) {
		struct sockaddr_in *sin;
		struct nhop4_extended nh_ext;

		sin = (struct sockaddr_in *)nmp->nm_nam;
		CURVNET_SET(CRED_TO_VNET(nmp->nm_sockreq.nr_cred));
		error = fib4_lookup_nh_ext(fibnum, sin->sin_addr, 0, 0,
		    &nh_ext);
		CURVNET_RESTORE();
		if (error != 0)
			return (NULL);

		if (IN_LOOPBACK(ntohl(nh_ext.nh_src.s_addr))) {
			/* Ignore loopback addresses */
			return (NULL);
		}

		*isinet6p = 0;
		*((struct in_addr *)paddr) = nh_ext.nh_src;

		return (u_int8_t *)paddr;
	}
#endif
#ifdef INET6
	if (nmp->nm_nam->sa_family == AF_INET6) {
		struct sockaddr_in6 *sin6;

		sin6 = (struct sockaddr_in6 *)nmp->nm_nam;

		CURVNET_SET(CRED_TO_VNET(nmp->nm_sockreq.nr_cred));
		error = in6_selectsrc_addr(fibnum, &sin6->sin6_addr,
		    sin6->sin6_scope_id, NULL, paddr, NULL);
		CURVNET_RESTORE();
		if (error != 0)
			return (NULL);

		if (IN6_IS_ADDR_LOOPBACK(paddr))
			return (NULL);

		/* Scope is embedded in */
		*isinet6p = 1;

		return (u_int8_t *)paddr;
	}
#endif
	return (NULL);
}
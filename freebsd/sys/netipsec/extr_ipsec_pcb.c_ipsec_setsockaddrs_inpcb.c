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
struct TYPE_2__ {scalar_t__* s6_addr16; } ;
struct sockaddr_in6 {int sin6_len; int sin_len; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; void* sin_family; void* sin6_scope_id; TYPE_1__ sin6_addr; int /*<<< orphan*/  sin6_port; void* sin6_family; } ;
union sockaddr_union {struct sockaddr_in6 sin; struct sockaddr_in6 sin6; } ;
typedef  scalar_t__ u_int ;
struct sockaddr_in {int sin6_len; int sin_len; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; void* sin_family; void* sin6_scope_id; TYPE_1__ sin6_addr; int /*<<< orphan*/  sin6_port; void* sin6_family; } ;
struct inpcb {int inp_vflag; int /*<<< orphan*/  inp_fport; int /*<<< orphan*/  inp_faddr; int /*<<< orphan*/  inp_lport; int /*<<< orphan*/  inp_laddr; TYPE_1__ in6p_faddr; TYPE_1__ in6p_laddr; } ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 scalar_t__ IN6_IS_SCOPE_LINKLOCAL (TYPE_1__*) ; 
 int INP_IPV4 ; 
 int INP_IPV6 ; 
 scalar_t__ IPSEC_DIR_OUTBOUND ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 void* ntohs (scalar_t__) ; 

__attribute__((used)) static void
ipsec_setsockaddrs_inpcb(struct inpcb *inp, union sockaddr_union *src,
    union sockaddr_union *dst, u_int dir)
{

#ifdef INET6
	if (inp->inp_vflag & INP_IPV6) {
		struct sockaddr_in6 *sin6;

		bzero(&src->sin6, sizeof(src->sin6));
		bzero(&dst->sin6, sizeof(dst->sin6));
		src->sin6.sin6_family = AF_INET6;
		src->sin6.sin6_len = sizeof(struct sockaddr_in6);
		dst->sin6.sin6_family = AF_INET6;
		dst->sin6.sin6_len = sizeof(struct sockaddr_in6);

		if (dir == IPSEC_DIR_OUTBOUND)
			sin6 = &src->sin6;
		else
			sin6 = &dst->sin6;
		sin6->sin6_addr = inp->in6p_laddr;
		sin6->sin6_port = inp->inp_lport;
		if (IN6_IS_SCOPE_LINKLOCAL(&inp->in6p_laddr)) {
			/* XXXAE: use in6p_zoneid */
			sin6->sin6_addr.s6_addr16[1] = 0;
			sin6->sin6_scope_id = ntohs(
			    inp->in6p_laddr.s6_addr16[1]);
		}

		if (dir == IPSEC_DIR_OUTBOUND)
			sin6 = &dst->sin6;
		else
			sin6 = &src->sin6;
		sin6->sin6_addr = inp->in6p_faddr;
		sin6->sin6_port = inp->inp_fport;
		if (IN6_IS_SCOPE_LINKLOCAL(&inp->in6p_faddr)) {
			/* XXXAE: use in6p_zoneid */
			sin6->sin6_addr.s6_addr16[1] = 0;
			sin6->sin6_scope_id = ntohs(
			    inp->in6p_faddr.s6_addr16[1]);
		}
	}
#endif
#ifdef INET
	if (inp->inp_vflag & INP_IPV4) {
		struct sockaddr_in *sin;

		bzero(&src->sin, sizeof(src->sin));
		bzero(&dst->sin, sizeof(dst->sin));
		src->sin.sin_family = AF_INET;
		src->sin.sin_len = sizeof(struct sockaddr_in);
		dst->sin.sin_family = AF_INET;
		dst->sin.sin_len = sizeof(struct sockaddr_in);

		if (dir == IPSEC_DIR_OUTBOUND)
			sin = &src->sin;
		else
			sin = &dst->sin;
		sin->sin_addr = inp->inp_laddr;
		sin->sin_port = inp->inp_lport;

		if (dir == IPSEC_DIR_OUTBOUND)
			sin = &dst->sin;
		else
			sin = &src->sin;
		sin->sin_addr = inp->inp_faddr;
		sin->sin_port = inp->inp_fport;
	}
#endif
}
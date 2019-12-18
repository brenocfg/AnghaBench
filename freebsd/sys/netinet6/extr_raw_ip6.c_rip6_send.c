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
typedef  int /*<<< orphan*/  tmp ;
struct thread {int dummy; } ;
struct socket {int so_state; } ;
struct sockaddr_in6 {scalar_t__ sin6_family; int sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr {int sa_len; } ;
struct mbuf {int dummy; } ;
struct inpcb {int /*<<< orphan*/  in6p_faddr; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNSPEC ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int EISCONN ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  INP_RLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_RUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int SS_ISCONNECTED ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in6*,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int rip6_output (struct mbuf*,struct socket*,struct sockaddr_in6*,struct mbuf*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

__attribute__((used)) static int
rip6_send(struct socket *so, int flags, struct mbuf *m, struct sockaddr *nam,
    struct mbuf *control, struct thread *td)
{
	struct inpcb *inp;
	struct sockaddr_in6 tmp;
	struct sockaddr_in6 *dst;
	int ret;

	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("rip6_send: inp == NULL"));

	/* Always copy sockaddr to avoid overwrites. */
	/* Unlocked read. */
	if (so->so_state & SS_ISCONNECTED) {
		if (nam) {
			m_freem(m);
			return (EISCONN);
		}
		/* XXX */
		bzero(&tmp, sizeof(tmp));
		tmp.sin6_family = AF_INET6;
		tmp.sin6_len = sizeof(struct sockaddr_in6);
		INP_RLOCK(inp);
		bcopy(&inp->in6p_faddr, &tmp.sin6_addr,
		    sizeof(struct in6_addr));
		INP_RUNLOCK(inp);
		dst = &tmp;
	} else {
		if (nam == NULL) {
			m_freem(m);
			return (ENOTCONN);
		}
		if (nam->sa_len != sizeof(struct sockaddr_in6)) {
			m_freem(m);
			return (EINVAL);
		}
		tmp = *(struct sockaddr_in6 *)nam;
		dst = &tmp;

		if (dst->sin6_family == AF_UNSPEC) {
			/*
			 * XXX: we allow this case for backward
			 * compatibility to buggy applications that
			 * rely on old (and wrong) kernel behavior.
			 */
			log(LOG_INFO, "rip6 SEND: address family is "
			    "unspec. Assume AF_INET6\n");
			dst->sin6_family = AF_INET6;
		} else if (dst->sin6_family != AF_INET6) {
			m_freem(m);
			return(EAFNOSUPPORT);
		}
	}
	ret = rip6_output(m, so, dst, control);
	return (ret);
}
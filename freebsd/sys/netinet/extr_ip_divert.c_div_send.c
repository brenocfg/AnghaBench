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
struct thread {int dummy; } ;
struct socket {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct mbuf {int m_len; } ;
struct ip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KMOD_IPSTAT_INC (int /*<<< orphan*/ ) ; 
 int div_output (struct socket*,struct mbuf*,struct sockaddr_in*,struct mbuf*) ; 
 int /*<<< orphan*/  ips_toosmall ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_pullup (struct mbuf*,int) ; 

__attribute__((used)) static int
div_send(struct socket *so, int flags, struct mbuf *m, struct sockaddr *nam,
    struct mbuf *control, struct thread *td)
{

	/* Packet must have a header (but that's about it) */
	if (m->m_len < sizeof (struct ip) &&
	    (m = m_pullup(m, sizeof (struct ip))) == NULL) {
		KMOD_IPSTAT_INC(ips_toosmall);
		m_freem(m);
		return EINVAL;
	}

	/* Send packet */
	return div_output(so, m, (struct sockaddr_in *)nam, control);
}
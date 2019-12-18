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
struct socket {int /*<<< orphan*/  so_rcv; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {int dummy; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ sbappendaddr (int /*<<< orphan*/ *,struct sockaddr*,struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  sorwakeup (struct socket*) ; 

__attribute__((used)) static int
socket_send(struct socket *s, struct mbuf *mm, struct sockaddr_in6 *src)
{

	if (s) {
		if (sbappendaddr(&s->so_rcv,
				 (struct sockaddr *)src,
				 mm, (struct mbuf *)0) != 0) {
			sorwakeup(s);
			return (0);
		}
	}
	m_freem(mm);
	return (-1);
}
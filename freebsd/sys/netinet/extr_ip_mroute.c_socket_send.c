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
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKBUF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ sbappendaddr_locked (int /*<<< orphan*/ *,struct sockaddr*,struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sorwakeup_locked (struct socket*) ; 

__attribute__((used)) static int
socket_send(struct socket *s, struct mbuf *mm, struct sockaddr_in *src)
{
    if (s) {
	SOCKBUF_LOCK(&s->so_rcv);
	if (sbappendaddr_locked(&s->so_rcv, (struct sockaddr *)src, mm,
	    NULL) != 0) {
	    sorwakeup_locked(s);
	    return 0;
	}
	SOCKBUF_UNLOCK(&s->so_rcv);
    }
    m_freem(mm);
    return -1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct mbuf {struct mbuf* m_next; scalar_t__ m_len; } ;
struct TYPE_3__ {scalar_t__ x_handy; scalar_t__ x_private; scalar_t__ x_base; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (struct mbuf*,char*) ; 

__attribute__((used)) static u_int
xdrmbuf_getpos(XDR *xdrs)
{
	struct mbuf *m0 = (struct mbuf *) xdrs->x_base;
	struct mbuf *m = (struct mbuf *) xdrs->x_private;
	u_int pos = 0;

	while (m0 && m0 != m) {
		pos += m0->m_len;
		m0 = m0->m_next;
	}
	KASSERT(m0, ("Corrupted mbuf chain"));

	return (pos + xdrs->x_handy);
}
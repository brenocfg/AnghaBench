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
struct mbuf {scalar_t__ m_len; struct mbuf* m_next; } ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {scalar_t__ x_handy; void* x_private; scalar_t__ x_base; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (struct mbuf*,char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static bool_t
xdrmbuf_setpos(XDR *xdrs, u_int pos)
{
	struct mbuf *m = (struct mbuf *) xdrs->x_base;

	while (m && pos > m->m_len) {
		pos -= m->m_len;
		m = m->m_next;
	}
	KASSERT(m, ("Corrupted mbuf chain"));

	xdrs->x_private = (void *) m;
	xdrs->x_handy = pos;

	return (TRUE);
}
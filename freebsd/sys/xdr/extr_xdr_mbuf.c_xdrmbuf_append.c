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
struct mbuf {int /*<<< orphan*/  m_len; struct mbuf* m_next; } ;
struct TYPE_3__ {scalar_t__ x_op; int /*<<< orphan*/  x_handy; struct mbuf* x_private; int /*<<< orphan*/ * x_ops; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ XDR_ENCODE ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_last (struct mbuf*) ; 
 scalar_t__ m_length (struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdrmbuf_ops ; 

void
xdrmbuf_append(XDR *xdrs, struct mbuf *madd)
{
	struct mbuf *m;

	KASSERT(xdrs->x_ops == &xdrmbuf_ops && xdrs->x_op == XDR_ENCODE,
	    ("xdrmbuf_append: invalid XDR stream"));

	if (m_length(madd, NULL) == 0) {
		m_freem(madd);
		return;
	}
	
	m = (struct mbuf *) xdrs->x_private;
	m->m_next = madd;

	m = m_last(madd);
	xdrs->x_private = m;
	xdrs->x_handy = m->m_len;
}
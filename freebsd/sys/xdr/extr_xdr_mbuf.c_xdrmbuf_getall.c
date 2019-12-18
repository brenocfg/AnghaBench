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
struct mbuf {struct mbuf* m_next; } ;
struct TYPE_3__ {scalar_t__ x_op; int /*<<< orphan*/  x_handy; int /*<<< orphan*/ * x_private; int /*<<< orphan*/ * x_base; int /*<<< orphan*/ * x_ops; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ XDR_DECODE ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* m_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdrmbuf_ops ; 

struct mbuf *
xdrmbuf_getall(XDR *xdrs)
{
	struct mbuf *m0, *m;

	KASSERT(xdrs->x_ops == &xdrmbuf_ops && xdrs->x_op == XDR_DECODE,
	    ("xdrmbuf_append: invalid XDR stream"));

	m0 = (struct mbuf *) xdrs->x_base;
	m = (struct mbuf *) xdrs->x_private;
	if (m0 != m) {
		while (m0->m_next != m)
			m0 = m0->m_next;
		m0->m_next = NULL;
		xdrs->x_private = NULL;
	} else {
		xdrs->x_base = NULL;
		xdrs->x_private = NULL;
	}

	if (m)
		m_adj(m, xdrs->x_handy);
	else
		m = m_get(M_WAITOK, MT_DATA);
	return (m);
}
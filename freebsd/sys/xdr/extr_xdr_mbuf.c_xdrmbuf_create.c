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
struct mbuf {scalar_t__ m_len; } ;
typedef  enum xdr_op { ____Placeholder_xdr_op } xdr_op ;
struct TYPE_3__ {int x_op; char* x_base; scalar_t__ x_handy; struct mbuf* x_private; int /*<<< orphan*/ * x_ops; } ;
typedef  TYPE_1__ XDR ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int XDR_ENCODE ; 
 struct mbuf* m_last (struct mbuf*) ; 
 int /*<<< orphan*/  xdrmbuf_ops ; 

void
xdrmbuf_create(XDR *xdrs, struct mbuf *m, enum xdr_op op)
{

	KASSERT(m != NULL, ("xdrmbuf_create with NULL mbuf chain"));
	xdrs->x_op = op;
	xdrs->x_ops = &xdrmbuf_ops;
	xdrs->x_base = (char *) m;
	if (op == XDR_ENCODE) {
		m = m_last(m);
		xdrs->x_private = m;
		xdrs->x_handy = m->m_len;
	} else {
		xdrs->x_private = m;
		xdrs->x_handy = 0;
	}
}
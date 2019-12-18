#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; scalar_t__ num; TYPE_1__* board; } ;
typedef  TYPE_2__ ct_chan_t ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLQ (int /*<<< orphan*/ ) ; 
 unsigned char GLQ_MASK ; 
 unsigned char GLQ_SHIFT ; 
 int T_G703 ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 

int ct_get_lq (ct_chan_t *c)
{
	unsigned char q1, q2, q3;
	static int lq_to_santibells [] = { 0, 95, 195, 285 };
	int i;

	if (! (c->type & T_G703))
		return 0;
	q1 = inb (GLQ (c->board->port));
	/* Repeat reading the register to produce a 10-usec delay. */
	for (i=0; i<20; ++i)
		q2 = inb (GLQ (c->board->port));
	for (i=0; i<20; ++i)
		q3 = inb (GLQ (c->board->port));
	if (c->num) {
		q1 >>= GLQ_SHIFT;
		q2 >>= GLQ_SHIFT;
		q3 >>= GLQ_SHIFT;
	}
	q1 &= GLQ_MASK;
	q2 &= GLQ_MASK;
	q3 &= GLQ_MASK;
	if (q1 <= q2 && q2 <= q3) return lq_to_santibells [q2];
	if (q2 <= q3 && q3 <= q1) return lq_to_santibells [q3];
	if (q3 <= q1 && q1 <= q2) return lq_to_santibells [q1];
	if (q1 <= q3 && q3 <= q2) return lq_to_santibells [q3];
	if (q3 <= q2 && q2 <= q1) return lq_to_santibells [q2];
	/* if (q2 <= q1 && q1 <= q3) */ return lq_to_santibells [q1];
}
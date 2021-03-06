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
union ring_state {scalar_t__ pidx_head; scalar_t__ pidx_tail; scalar_t__ cidx; scalar_t__ flags; int /*<<< orphan*/  state; } ;
struct mp_ring {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ IDLE ; 

int
mp_ring_is_idle(struct mp_ring *r)
{
	union ring_state s;

	s.state = r->state;
	if (s.pidx_head == s.pidx_tail && s.pidx_tail == s.cidx &&
	    s.flags == IDLE)
		return (1);

	return (0);
}
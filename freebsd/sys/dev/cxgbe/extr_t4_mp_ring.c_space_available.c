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
union ring_state {scalar_t__ cidx; scalar_t__ pidx_head; } ;
typedef  scalar_t__ uint16_t ;
struct mp_ring {scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static inline uint16_t
space_available(struct mp_ring *r, union ring_state s)
{
	uint16_t x = r->size - 1;

	if (s.cidx == s.pidx_head)
		return (x);
	else if (s.cidx > s.pidx_head)
		return (s.cidx - s.pidx_head - 1);
	else
		return (x - s.pidx_head + s.cidx);
}
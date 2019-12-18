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
struct cpack_state {scalar_t__ c_next; scalar_t__ c_buf; scalar_t__ c_len; } ;

/* Variables and functions */

int
cpack_advance(struct cpack_state *cs, const size_t toskip)
{
	/* No space left? */
	if (cs->c_next - cs->c_buf + toskip > cs->c_len)
		return -1;
	cs->c_next += toskip;
	return 0;
}
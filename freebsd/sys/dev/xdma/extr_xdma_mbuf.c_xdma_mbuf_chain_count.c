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
typedef  scalar_t__ uint32_t ;
struct mbuf {struct mbuf* m_next; } ;

/* Variables and functions */

uint32_t
xdma_mbuf_chain_count(struct mbuf *m0)
{
	struct mbuf *m;
	uint32_t c;

	c = 0;

	for (m = m0; m != NULL; m = m->m_next)
		c++;

	return (c);
}
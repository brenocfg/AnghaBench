#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_6__ {int addr_low; } ;
typedef  TYPE_1__ mcp_kreq_ether_recv_t ;

/* Variables and functions */
 int /*<<< orphan*/  mxge_pio_copy (TYPE_1__ volatile*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void
mxge_submit_8rx(volatile mcp_kreq_ether_recv_t *dst,
		mcp_kreq_ether_recv_t *src)
{
	uint32_t low;

	low = src->addr_low;
	src->addr_low = 0xffffffff;
	mxge_pio_copy(dst, src, 4 * sizeof (*src));
	wmb();
	mxge_pio_copy(dst + 4, src + 4, 4 * sizeof (*src));
	wmb();
	src->addr_low = low;
	dst->addr_low = low;
	wmb();
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct xlocale_collate {TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pri_count; } ;

/* Variables and functions */
 int XFRM_MASK ; 
 int XFRM_OFFSET ; 
 int XFRM_SHIFT ; 

__attribute__((used)) static int
xfrm(struct xlocale_collate *table, unsigned char *p, int pri, int pass)
{
	/* we use unsigned to ensure zero fill on right shift */
	uint32_t val = (uint32_t)table->info->pri_count[pass];
	int nc = 0;

	while (val) {
		*p = (pri & XFRM_MASK) + XFRM_OFFSET;
		pri >>= XFRM_SHIFT;
		val >>= XFRM_SHIFT;
		p++;
		nc++;
	}
	return (nc);
}
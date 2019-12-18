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
struct ubsec_operand {int nsegs; TYPE_1__* segs; } ;
struct TYPE_2__ {int ds_addr; int ds_len; } ;

/* Variables and functions */

__attribute__((used)) static int
ubsec_dmamap_aligned(struct ubsec_operand *op)
{
	int i;

	for (i = 0; i < op->nsegs; i++) {
		if (op->segs[i].ds_addr & 3)
			return (0);
		if ((i != (op->nsegs - 1)) &&
		    (op->segs[i].ds_len & 3))
			return (0);
	}
	return (1);
}
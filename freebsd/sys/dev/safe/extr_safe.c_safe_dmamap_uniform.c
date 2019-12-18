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
struct safe_operand {scalar_t__ nsegs; TYPE_1__* segs; } ;
struct TYPE_2__ {int ds_len; } ;

/* Variables and functions */
 int SAFE_MAX_DSIZE ; 

__attribute__((used)) static int
safe_dmamap_uniform(const struct safe_operand *op)
{
	int result = 1;

	if (op->nsegs > 0) {
		int i;

		for (i = 0; i < op->nsegs-1; i++) {
			if (op->segs[i].ds_len % SAFE_MAX_DSIZE)
				return (0);
			if (op->segs[i].ds_len != SAFE_MAX_DSIZE)
				result = 2;
		}
	}
	return (result);
}
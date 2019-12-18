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
struct blk_rq_stat {int nr_samples; int mean; scalar_t__ batch; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int div_u64 (scalar_t__,int) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void blk_rq_stat_sum(struct blk_rq_stat *dst, struct blk_rq_stat *src)
{
	if (!src->nr_samples)
		return;

	dst->min = min(dst->min, src->min);
	dst->max = max(dst->max, src->max);

	dst->mean = div_u64(src->batch + dst->mean * dst->nr_samples,
				dst->nr_samples + src->nr_samples);

	dst->nr_samples += src->nr_samples;
}
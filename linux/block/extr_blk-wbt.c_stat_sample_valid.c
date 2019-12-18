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
struct blk_rq_stat {int nr_samples; } ;

/* Variables and functions */
 size_t READ ; 
 int RWB_MIN_WRITE_SAMPLES ; 
 size_t WRITE ; 

__attribute__((used)) static inline bool stat_sample_valid(struct blk_rq_stat *stat)
{
	/*
	 * We need at least one read sample, and a minimum of
	 * RWB_MIN_WRITE_SAMPLES. We require some write samples to know
	 * that it's writes impacting us, and not just some sole read on
	 * a device that is in a lower power state.
	 */
	return (stat[READ].nr_samples >= 1 &&
		stat[WRITE].nr_samples >= RWB_MIN_WRITE_SAMPLES);
}
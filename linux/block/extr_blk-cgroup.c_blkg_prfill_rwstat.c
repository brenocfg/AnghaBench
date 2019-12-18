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
typedef  int /*<<< orphan*/  u64 ;
struct seq_file {int dummy; } ;
struct blkg_rwstat_sample {int dummy; } ;
struct blkg_policy_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __blkg_prfill_rwstat (struct seq_file*,struct blkg_policy_data*,struct blkg_rwstat_sample*) ; 
 int /*<<< orphan*/  blkg_rwstat_read (void*,struct blkg_rwstat_sample*) ; 

u64 blkg_prfill_rwstat(struct seq_file *sf, struct blkg_policy_data *pd,
		       int off)
{
	struct blkg_rwstat_sample rwstat = { };

	blkg_rwstat_read((void *)pd + off, &rwstat);
	return __blkg_prfill_rwstat(sf, pd, &rwstat);
}
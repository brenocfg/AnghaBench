#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  nr_samples; } ;
struct TYPE_3__ {int /*<<< orphan*/  total; } ;
struct latency_stat {TYPE_2__ rqs; TYPE_1__ ps; } ;
struct iolatency_grp {scalar_t__ ssd; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 latency_stat_samples(struct iolatency_grp *iolat,
				       struct latency_stat *stat)
{
	if (iolat->ssd)
		return stat->ps.total;
	return stat->rqs.nr_samples;
}
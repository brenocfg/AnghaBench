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
struct TYPE_2__ {scalar_t__ missed; scalar_t__ total; } ;
struct latency_stat {int /*<<< orphan*/  rqs; TYPE_1__ ps; } ;
struct iolatency_grp {scalar_t__ ssd; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_rq_stat_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void latency_stat_init(struct iolatency_grp *iolat,
				     struct latency_stat *stat)
{
	if (iolat->ssd) {
		stat->ps.total = 0;
		stat->ps.missed = 0;
	} else
		blk_rq_stat_init(&stat->rqs);
}
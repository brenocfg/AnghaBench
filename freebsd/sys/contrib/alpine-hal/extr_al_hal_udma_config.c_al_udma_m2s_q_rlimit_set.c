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
struct udma_rlimit_common {int dummy; } ;
struct al_udma_q {TYPE_2__* q_regs; } ;
struct al_udma_m2s_rlimit_cfg {int dummy; } ;
struct TYPE_3__ {struct udma_rlimit_common rlimit; } ;
struct TYPE_4__ {TYPE_1__ m2s_q; } ;

/* Variables and functions */
 int al_udma_common_rlimit_set (struct udma_rlimit_common*,struct al_udma_m2s_rlimit_cfg*) ; 

int al_udma_m2s_q_rlimit_set(struct al_udma_q *udma_q,
				struct al_udma_m2s_rlimit_cfg *conf)
{
	struct udma_rlimit_common *rlimit_regs = &udma_q->q_regs->m2s_q.rlimit;

	return al_udma_common_rlimit_set(rlimit_regs, conf);
}
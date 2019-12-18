#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct udma_rlimit_common {int dummy; } ;
struct al_udma {int /*<<< orphan*/  name; TYPE_3__* udma_regs; } ;
typedef  enum al_udma_m2s_rlimit_action { ____Placeholder_al_udma_m2s_rlimit_action } al_udma_m2s_rlimit_action ;
struct TYPE_4__ {struct udma_rlimit_common rlimit; } ;
struct TYPE_5__ {TYPE_1__ m2s_stream_rate_limiter; } ;
struct TYPE_6__ {TYPE_2__ m2s; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ,int) ; 
 int al_udma_common_rlimit_act (struct udma_rlimit_common*,int) ; 

int al_udma_m2s_strm_rlimit_act(struct al_udma *udma,
				enum al_udma_m2s_rlimit_action act)
{
	struct udma_rlimit_common *rlimit_regs =
	    &udma->udma_regs->m2s.m2s_stream_rate_limiter.rlimit;

	if (al_udma_common_rlimit_act(rlimit_regs, act) == -EINVAL) {
		al_err("udma [%s]: udma stream rate limit invalid action "
			"(%d)\n", udma->name, act);
		return -EINVAL;
	}
	return 0;
}
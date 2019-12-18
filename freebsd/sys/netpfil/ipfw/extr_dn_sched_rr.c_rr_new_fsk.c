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
struct rr_schk {int q_bytes; int min_q; int max_q; } ;
struct TYPE_2__ {int /*<<< orphan*/ * par; } ;
struct dn_fsk {TYPE_1__ fs; scalar_t__ sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipdn_bound_var (int /*<<< orphan*/ *,int,int,int,char*) ; 

__attribute__((used)) static int
rr_new_fsk(struct dn_fsk *fs)
{
	struct rr_schk *schk = (struct rr_schk *)(fs->sched + 1);
	/* par[0] is the weight, par[1] is the quantum step */
	/* make sure the product fits an uint32_t */
	ipdn_bound_var(&fs->fs.par[0], 1,
		1, 65536, "RR weight");
	ipdn_bound_var(&fs->fs.par[1], schk->q_bytes,
		schk->min_q, schk->max_q, "RR quantum");
	return 0;
}
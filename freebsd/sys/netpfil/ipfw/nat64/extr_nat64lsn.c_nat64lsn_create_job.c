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
struct nat64lsn_job_item {int jtype; scalar_t__ done; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;
struct nat64lsn_cfg {scalar_t__ jlen; scalar_t__ jmaxlen; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DP_DROPS ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NAT64STAT_INC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dropped ; 
 int /*<<< orphan*/  jmaxlen ; 
 int /*<<< orphan*/  jnomem ; 
 int /*<<< orphan*/  nat64lsn_job_zone ; 
 struct nat64lsn_job_item* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nat64lsn_job_item *
nat64lsn_create_job(struct nat64lsn_cfg *cfg, int jtype)
{
	struct nat64lsn_job_item *ji;

	/*
	 * Do not try to lock possibly contested mutex if we're near the
	 * limit. Drop packet instead.
	 */
	ji = NULL;
	if (cfg->jlen >= cfg->jmaxlen)
		NAT64STAT_INC(&cfg->base.stats, jmaxlen);
	else {
		ji = uma_zalloc(nat64lsn_job_zone, M_NOWAIT);
		if (ji == NULL)
			NAT64STAT_INC(&cfg->base.stats, jnomem);
	}
	if (ji == NULL) {
		NAT64STAT_INC(&cfg->base.stats, dropped);
		DPRINTF(DP_DROPS, "failed to create job");
	} else {
		ji->jtype = jtype;
		ji->done = 0;
	}
	return (ji);
}
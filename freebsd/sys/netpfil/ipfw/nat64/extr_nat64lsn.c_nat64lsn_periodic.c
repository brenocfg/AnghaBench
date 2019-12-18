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
struct nat64lsn_job_item {int /*<<< orphan*/  epoch_ctx; int /*<<< orphan*/  pgchunk; int /*<<< orphan*/  portgroups; int /*<<< orphan*/  hosts; int /*<<< orphan*/  jtype; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;
struct nat64lsn_cfg {scalar_t__ hosts_count; int /*<<< orphan*/  periodic; TYPE_1__ base; int /*<<< orphan*/  vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JTYPE_DESTROY ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NAT64LSN_EPOCH_CALL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAT64STAT_INC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PERIODIC_DELAY ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int) ; 
 int hz ; 
 int /*<<< orphan*/  jnomem ; 
 int /*<<< orphan*/  nat64lsn_expire_hosts (struct nat64lsn_cfg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nat64lsn_expire_pgchunk (struct nat64lsn_cfg*) ; 
 int /*<<< orphan*/  nat64lsn_expire_portgroups (struct nat64lsn_cfg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nat64lsn_job_destroy ; 
 int /*<<< orphan*/  nat64lsn_job_zone ; 
 struct nat64lsn_job_item* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nat64lsn_periodic(void *data)
{
	struct nat64lsn_job_item *ji;
	struct nat64lsn_cfg *cfg;

	cfg = (struct nat64lsn_cfg *) data;
	CURVNET_SET(cfg->vp);
	if (cfg->hosts_count > 0) {
		ji = uma_zalloc(nat64lsn_job_zone, M_NOWAIT);
		if (ji != NULL) {
			ji->jtype = JTYPE_DESTROY;
			CK_SLIST_INIT(&ji->hosts);
			CK_SLIST_INIT(&ji->portgroups);
			nat64lsn_expire_hosts(cfg, &ji->hosts);
			nat64lsn_expire_portgroups(cfg, &ji->portgroups);
			ji->pgchunk = nat64lsn_expire_pgchunk(cfg);
			NAT64LSN_EPOCH_CALL(&ji->epoch_ctx,
			    nat64lsn_job_destroy);
		} else
			NAT64STAT_INC(&cfg->base.stats, jnomem);
	}
	callout_schedule(&cfg->periodic, hz * PERIODIC_DELAY);
	CURVNET_RESTORE();
}
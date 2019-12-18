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
struct nat64lsn_job_item {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;
struct nat64lsn_cfg {int /*<<< orphan*/  jcallout; int /*<<< orphan*/  jlen; TYPE_1__ base; int /*<<< orphan*/  jhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  JQUEUE_LOCK () ; 
 int /*<<< orphan*/  JQUEUE_UNLOCK () ; 
 int /*<<< orphan*/  NAT64STAT_INC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct nat64lsn_job_item*,int /*<<< orphan*/ ) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct nat64lsn_cfg*) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  jrequests ; 
 int /*<<< orphan*/  nat64lsn_do_request ; 

__attribute__((used)) static void
nat64lsn_enqueue_job(struct nat64lsn_cfg *cfg, struct nat64lsn_job_item *ji)
{

	JQUEUE_LOCK();
	STAILQ_INSERT_TAIL(&cfg->jhead, ji, entries);
	NAT64STAT_INC(&cfg->base.stats, jrequests);
	cfg->jlen++;

	if (callout_pending(&cfg->jcallout) == 0)
		callout_reset(&cfg->jcallout, 1, nat64lsn_do_request, cfg);
	JQUEUE_UNLOCK();
}
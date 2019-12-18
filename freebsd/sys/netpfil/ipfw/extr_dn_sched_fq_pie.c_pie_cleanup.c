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
struct pie_status {int /*<<< orphan*/  lock_mtx; int /*<<< orphan*/  aqm_pie_callout; } ;
struct fq_pie_flow {struct pie_status pst; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBT_1US ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fq_pie_flow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fqpie_callout_cleanup ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pie_cleanup(struct fq_pie_flow *q)
{
	struct pie_status *pst  = &q->pst;

	mtx_lock(&pst->lock_mtx);
	callout_reset_sbt(&pst->aqm_pie_callout,
		SBT_1US, 0, fqpie_callout_cleanup, q, 0);
	mtx_unlock(&pst->lock_mtx);
	return 0;
}
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
struct qman_fq {int dummy; } ;
struct qm_mcr_queryfq_np {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  frm_cnt ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qm_mcr_np_get (struct qm_mcr_queryfq_np*,int /*<<< orphan*/ ) ; 
 int qman_query_fq_np (struct qman_fq*,struct qm_mcr_queryfq_np*) ; 

__attribute__((used)) static int empty_caam_fq(struct qman_fq *fq)
{
	int ret;
	struct qm_mcr_queryfq_np np;

	/* Wait till the older CAAM FQ get empty */
	do {
		ret = qman_query_fq_np(fq, &np);
		if (ret)
			return ret;

		if (!qm_mcr_np_get(&np, frm_cnt))
			break;

		msleep(20);
	} while (1);

	/*
	 * Give extra time for pending jobs from this FQ in holding tanks
	 * to get processed
	 */
	msleep(20);
	return 0;
}
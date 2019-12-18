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
typedef  size_t u16 ;
struct ixl_pf_qtag {scalar_t__ type; size_t num_allocated; size_t* qidx; int /*<<< orphan*/ * qmgr; } ;
struct ixl_pf_qmgr {int /*<<< orphan*/ * qinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IXL_PF_QALLOC_SCATTERED ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

int
ixl_pf_qmgr_release(struct ixl_pf_qmgr *qmgr, struct ixl_pf_qtag *qtag)
{
	u16 i, qidx;

	if (qtag == NULL)
		return (EINVAL);

	if (qtag->type == IXL_PF_QALLOC_SCATTERED) {
		for (i = 0; i < qtag->num_allocated; i++) {
			qidx = qtag->qidx[i];
			bzero(&qmgr->qinfo[qidx], sizeof(qmgr->qinfo[qidx]));
		}
	} else {
		u16 first_index = qtag->qidx[0];
		for (i = first_index; i < first_index + qtag->num_allocated; i++)
			bzero(&qmgr->qinfo[i], sizeof(qmgr->qinfo[qidx]));
	}

	qtag->qmgr = NULL;
	return (0);
}
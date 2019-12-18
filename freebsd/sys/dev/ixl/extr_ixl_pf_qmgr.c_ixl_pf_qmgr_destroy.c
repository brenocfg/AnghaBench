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
struct ixl_pf_qmgr {int /*<<< orphan*/ * qinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IXL ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ixl_pf_qmgr_destroy(struct ixl_pf_qmgr *qmgr)
{
	free(qmgr->qinfo, M_IXL);
	qmgr->qinfo = NULL;
}
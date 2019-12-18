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
typedef  size_t u32 ;
struct ecore_src_iids {int /*<<< orphan*/  pf_cids; int /*<<< orphan*/  per_vf_cids; } ;
struct ecore_cxt_mngr {scalar_t__ arfs_count; TYPE_1__* conn_cfg; } ;
struct TYPE_2__ {scalar_t__ cids_per_vf; scalar_t__ cid_count; } ;

/* Variables and functions */
 size_t MAX_CONN_TYPES ; 
 int /*<<< orphan*/  src_proto (size_t) ; 

__attribute__((used)) static void ecore_cxt_src_iids(struct ecore_cxt_mngr *p_mngr,
			       struct ecore_src_iids *iids)
{
	u32 i;

	for (i = 0; i < MAX_CONN_TYPES; i++) {
		if (!src_proto(i))
			continue;

		iids->pf_cids += p_mngr->conn_cfg[i].cid_count;
		iids->per_vf_cids += p_mngr->conn_cfg[i].cids_per_vf;
	}

	/* Add L2 filtering filters in addition */
	iids->pf_cids += p_mngr->arfs_count;
}
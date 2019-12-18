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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct ecore_hwfn {struct ecore_cxt_mngr* p_cxt_mngr; } ;
struct ecore_cxt_mngr {struct ecore_cid_acquired_map** acquired_vf; struct ecore_cid_acquired_map* acquired; } ;
struct ecore_cid_acquired_map {scalar_t__ start_cid; scalar_t__ max_count; int /*<<< orphan*/  cid_map; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,scalar_t__,size_t) ; 
 size_t ECORE_CXT_PF_CID ; 
 int MAX_CONN_TYPES ; 
 struct ecore_cid_acquired_map* OSAL_NULL ; 
 int /*<<< orphan*/  OSAL_TEST_BIT (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ecore_cxt_test_cid_acquired(struct ecore_hwfn *p_hwfn,
					u32 cid, u8 vfid,
					enum protocol_type *p_type,
					struct ecore_cid_acquired_map **pp_map)
{
	struct ecore_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 rel_cid;

	/* Iterate over protocols and find matching cid range */
	for (*p_type = 0; *p_type < MAX_CONN_TYPES; (*p_type)++) {
		if (vfid == ECORE_CXT_PF_CID)
			*pp_map = &p_mngr->acquired[*p_type];
		else
			*pp_map = &p_mngr->acquired_vf[*p_type][vfid];

		if (!((*pp_map)->cid_map))
			continue;
		if (cid >= (*pp_map)->start_cid &&
		    cid < (*pp_map)->start_cid + (*pp_map)->max_count) {
			break;
		}
	}

	if (*p_type == MAX_CONN_TYPES) {
		DP_NOTICE(p_hwfn, true, "Invalid CID %d vfid %02x", cid, vfid);
		goto fail;
	}

	rel_cid = cid - (*pp_map)->start_cid;
	if (!OSAL_TEST_BIT(rel_cid, (*pp_map)->cid_map)) {
		DP_NOTICE(p_hwfn, true,
			  "CID %d [vifd %02x] not acquired", cid, vfid);
		goto fail;
	}

	return true;
fail:
	*p_type = MAX_CONN_TYPES;
	*pp_map = OSAL_NULL;
	return false;
}
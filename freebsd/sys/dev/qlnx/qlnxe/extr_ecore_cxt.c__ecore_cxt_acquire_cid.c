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
struct ecore_cid_acquired_map {scalar_t__ cid_map; scalar_t__ max_count; scalar_t__ start_cid; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 size_t COMMON_MAX_NUM_VFS ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,size_t,int) ; 
 size_t ECORE_CXT_PF_CID ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_CXT ; 
 int ECORE_NORESOURCES ; 
 int ECORE_SUCCESS ; 
 int MAX_CONN_TYPES ; 
 scalar_t__ OSAL_FIND_FIRST_ZERO_BIT (scalar_t__,scalar_t__) ; 
 scalar_t__ OSAL_NULL ; 
 int /*<<< orphan*/  OSAL_SET_BIT (scalar_t__,scalar_t__) ; 

enum _ecore_status_t _ecore_cxt_acquire_cid(struct ecore_hwfn *p_hwfn,
					    enum protocol_type type,
					    u32 *p_cid, u8 vfid)
{
	struct ecore_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	struct ecore_cid_acquired_map *p_map;
	u32 rel_cid;

	if (type >= MAX_CONN_TYPES) {
		DP_NOTICE(p_hwfn, true, "Invalid protocol type %d", type);
		return ECORE_INVAL;
	}

	if (vfid >= COMMON_MAX_NUM_VFS && vfid != ECORE_CXT_PF_CID) {
		DP_NOTICE(p_hwfn, true, "VF [%02x] is out of range\n", vfid);
		return ECORE_INVAL;
	}

	/* Determine the right map to take this CID from */
	if (vfid == ECORE_CXT_PF_CID)
		p_map = &p_mngr->acquired[type];
	else
		p_map = &p_mngr->acquired_vf[type][vfid];

	if (p_map->cid_map == OSAL_NULL) {
		DP_NOTICE(p_hwfn, true, "Invalid protocol type %d", type);
		return ECORE_INVAL;
	}

	rel_cid = OSAL_FIND_FIRST_ZERO_BIT(p_map->cid_map,
					   p_map->max_count);

	if (rel_cid >= p_map->max_count) {
		DP_NOTICE(p_hwfn, false, "no CID available for protocol %d\n",
			  type);
		return ECORE_NORESOURCES;
	}

	OSAL_SET_BIT(rel_cid, p_map->cid_map);

	*p_cid = rel_cid + p_map->start_cid;

	DP_VERBOSE(p_hwfn, ECORE_MSG_CXT,
		   "Acquired cid 0x%08x [rel. %08x] vfid %02x type %d\n",
		   *p_cid, rel_cid, vfid, type);

	return ECORE_SUCCESS;
}
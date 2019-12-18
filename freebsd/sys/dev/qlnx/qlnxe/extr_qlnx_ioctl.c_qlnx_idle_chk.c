#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct TYPE_5__ {struct ecore_hwfn* hwfns; } ;
struct TYPE_6__ {int* idle_chk_size; int idle_chk_taken; int /*<<< orphan*/ * idle_chk; TYPE_1__ cdev; scalar_t__* idle_chk_dwords; } ;
typedef  TYPE_2__ qlnx_host_t ;

/* Variables and functions */
 int DBG_STATUS_OK ; 
 int EINVAL ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  ecore_dbg_get_fw_func_ver () ; 
 int ecore_dbg_idle_chk_dump (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  ecore_dbg_set_app_ver (int /*<<< orphan*/ ) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 

int
qlnx_idle_chk(qlnx_host_t *ha, uint32_t *num_dumped_dwords, int hwfn_index)
{
	int rval = EINVAL;
	struct ecore_hwfn *p_hwfn;
	struct ecore_ptt *p_ptt;

	if (ha->idle_chk_dwords[hwfn_index]) {
		/* the idle check is already available */
		*num_dumped_dwords = ha->idle_chk_dwords[hwfn_index];
		return (0);
	}

	ecore_dbg_set_app_ver(ecore_dbg_get_fw_func_ver());

	p_hwfn = &ha->cdev.hwfns[hwfn_index];
	p_ptt = ecore_ptt_acquire(p_hwfn);

	if (!p_ptt) {
		QL_DPRINT1(ha,"ecore_ptt_acquire failed\n");
		return (rval);
	}

	if ((rval = ecore_dbg_idle_chk_dump(p_hwfn, p_ptt,
			ha->idle_chk[hwfn_index],
			(ha->idle_chk_size[hwfn_index] >> 2),
			num_dumped_dwords)) == DBG_STATUS_OK) {
	 	rval = 0;	
		ha->idle_chk_taken = 1;
	} else
		QL_DPRINT1(ha,"ecore_dbg_idle_chk_dump failed [%d, 0x%x]\n",
			   hwfn_index, rval);

	ecore_ptt_release(p_hwfn, p_ptt);

	return (rval);
}
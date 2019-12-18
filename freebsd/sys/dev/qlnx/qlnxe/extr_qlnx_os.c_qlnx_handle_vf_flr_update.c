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
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT1 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  __qlnx_vf_flr_update (struct ecore_hwfn*) ; 
 int ecore_iov_vf_flr_cleanup (struct ecore_hwfn*,struct ecore_ptt*) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 

__attribute__((used)) static void
qlnx_handle_vf_flr_update(qlnx_host_t *ha, struct ecore_hwfn *p_hwfn)
{
        struct ecore_ptt *ptt;
	int ret;

	ptt = ecore_ptt_acquire(p_hwfn);

	if (!ptt) {
                QL_DPRINT1(ha, "Can't acquire PTT; re-scheduling\n");
		__qlnx_vf_flr_update(p_hwfn);
                return;
	}

	ret = ecore_iov_vf_flr_cleanup(p_hwfn, ptt);

	if (ret) {
                QL_DPRINT1(ha, "ecore_iov_vf_flr_cleanup failed; re-scheduling\n");
	}
		
	ecore_ptt_release(p_hwfn, ptt);

	return;
}
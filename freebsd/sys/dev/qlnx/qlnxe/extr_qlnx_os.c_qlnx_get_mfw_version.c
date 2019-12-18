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
typedef  int /*<<< orphan*/  uint32_t ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct TYPE_5__ {struct ecore_hwfn* hwfns; } ;
struct TYPE_6__ {TYPE_1__ cdev; } ;
typedef  TYPE_2__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ecore_mcp_get_mfw_ver (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 

__attribute__((used)) static int
qlnx_get_mfw_version(qlnx_host_t *ha, uint32_t *mfw_ver)
{
	struct ecore_hwfn	*p_hwfn;
	struct ecore_ptt	*p_ptt;

	p_hwfn = &ha->cdev.hwfns[0];
	p_ptt = ecore_ptt_acquire(p_hwfn);

	if (p_ptt ==  NULL) {
                QL_DPRINT1(ha, "ecore_ptt_acquire failed\n");
                return (-1);
	}
	ecore_mcp_get_mfw_ver(p_hwfn, p_ptt, mfw_ver, NULL);
	
	ecore_ptt_release(p_hwfn, p_ptt);

	return (0);
}
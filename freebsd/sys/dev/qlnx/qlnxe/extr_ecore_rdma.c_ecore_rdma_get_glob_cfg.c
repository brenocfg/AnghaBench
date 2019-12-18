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
struct ecore_rdma_glob_cfg {int dummy; } ;
struct ecore_hwfn {TYPE_1__* p_rdma_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  glob_cfg; } ;

/* Variables and functions */
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MEMCPY (struct ecore_rdma_glob_cfg*,int /*<<< orphan*/ *,int) ; 

enum _ecore_status_t
ecore_rdma_get_glob_cfg(struct ecore_hwfn *p_hwfn,
			struct ecore_rdma_glob_cfg *out_params)
{
	OSAL_MEMCPY(out_params, &p_hwfn->p_rdma_info->glob_cfg,
		    sizeof(struct ecore_rdma_glob_cfg));

	return ECORE_SUCCESS;
}
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
struct init_qm_vport_params {int dummy; } ;
struct init_qm_pq_params {int dummy; } ;
struct init_qm_port_params {int dummy; } ;
struct ecore_wfq_data {int dummy; } ;
struct ecore_qm_info {void* wfq_data; void* qm_port_params; void* qm_vport_params; void* qm_pq_params; } ;
struct ecore_hwfn {TYPE_1__* p_dev; struct ecore_qm_info qm_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {int num_ports_in_engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* OSAL_ZALLOC (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int ecore_init_qm_get_num_pqs (struct ecore_hwfn*) ; 
 int ecore_init_qm_get_num_vports (struct ecore_hwfn*) ; 
 int ecore_init_qm_sanity (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_qm_info_free (struct ecore_hwfn*) ; 

__attribute__((used)) static enum _ecore_status_t ecore_alloc_qm_data(struct ecore_hwfn *p_hwfn)
{
	struct ecore_qm_info *qm_info = &p_hwfn->qm_info;
	enum _ecore_status_t rc;

	rc = ecore_init_qm_sanity(p_hwfn);
	if (rc != ECORE_SUCCESS)
		goto alloc_err;

	qm_info->qm_pq_params = OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL,
					    sizeof(struct init_qm_pq_params) *
					    ecore_init_qm_get_num_pqs(p_hwfn));
	if (!qm_info->qm_pq_params)
		goto alloc_err;

	qm_info->qm_vport_params = OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL,
					       sizeof(struct init_qm_vport_params) *
					       ecore_init_qm_get_num_vports(p_hwfn));
	if (!qm_info->qm_vport_params)
		goto alloc_err;

	qm_info->qm_port_params = OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL,
					      sizeof(struct init_qm_port_params) *
					      p_hwfn->p_dev->num_ports_in_engine);
	if (!qm_info->qm_port_params)
		goto alloc_err;

	qm_info->wfq_data = OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL,
					sizeof(struct ecore_wfq_data) *
					ecore_init_qm_get_num_vports(p_hwfn));
	if (!qm_info->wfq_data)
		goto alloc_err;

	return ECORE_SUCCESS;

alloc_err:
	DP_NOTICE(p_hwfn, false, "Failed to allocate memory for QM params\n");
	ecore_qm_info_free(p_hwfn);
	return ECORE_NOMEM;
}
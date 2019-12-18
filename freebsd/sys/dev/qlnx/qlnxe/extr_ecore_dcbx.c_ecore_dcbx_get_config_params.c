#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ecore_hwfn {int /*<<< orphan*/  p_dev; TYPE_4__* p_dcbx_info; } ;
struct ecore_dcbx_set {int dummy; } ;
struct TYPE_8__ {int valid; struct ecore_dcbx_set params; } ;
struct TYPE_10__ {TYPE_3__ config; struct ecore_dcbx_set dscp; int /*<<< orphan*/  enabled; int /*<<< orphan*/  ver_num; scalar_t__ override_flags; } ;
struct TYPE_7__ {TYPE_5__ params; int /*<<< orphan*/  enabled; scalar_t__ local; scalar_t__ ieee; scalar_t__ cee; } ;
struct ecore_dcbx_get {TYPE_2__ operational; } ;
struct ecore_dcbx_dscp_params {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_6__ {TYPE_5__ dscp; } ;
struct TYPE_9__ {TYPE_5__ set; TYPE_1__ get; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCBX_CONFIG_VERSION_CEE ; 
 int /*<<< orphan*/  DCBX_CONFIG_VERSION_DISABLED ; 
 int /*<<< orphan*/  DCBX_CONFIG_VERSION_IEEE ; 
 int /*<<< orphan*/  DCBX_CONFIG_VERSION_STATIC ; 
 int /*<<< orphan*/  ECORE_DCBX_OPERATIONAL_MIB ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ecore_dcbx_get* OSAL_ALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,struct ecore_dcbx_get*) ; 
 int /*<<< orphan*/  OSAL_MEMCPY (struct ecore_dcbx_set*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_dcbx_get*,int /*<<< orphan*/ ,int) ; 
 int ecore_dcbx_query_params (struct ecore_hwfn*,struct ecore_dcbx_get*,int /*<<< orphan*/ ) ; 

enum _ecore_status_t ecore_dcbx_get_config_params(struct ecore_hwfn *p_hwfn,
						  struct ecore_dcbx_set *params)
{
	struct ecore_dcbx_get *dcbx_info;
	enum _ecore_status_t rc;

	if (p_hwfn->p_dcbx_info->set.config.valid) {
		OSAL_MEMCPY(params, &p_hwfn->p_dcbx_info->set,
			    sizeof(struct ecore_dcbx_set));
		return ECORE_SUCCESS;
	}

	dcbx_info = OSAL_ALLOC(p_hwfn->p_dev, GFP_KERNEL,
			       sizeof(*dcbx_info));
	if (!dcbx_info)
		return ECORE_NOMEM;

	OSAL_MEMSET(dcbx_info, 0, sizeof(*dcbx_info));
	rc = ecore_dcbx_query_params(p_hwfn, dcbx_info,
				     ECORE_DCBX_OPERATIONAL_MIB);
	if (rc) {
		OSAL_FREE(p_hwfn->p_dev, dcbx_info);
		return rc;
	}
	p_hwfn->p_dcbx_info->set.override_flags = 0;

	p_hwfn->p_dcbx_info->set.ver_num = DCBX_CONFIG_VERSION_DISABLED;
	if (dcbx_info->operational.cee)
		p_hwfn->p_dcbx_info->set.ver_num |= DCBX_CONFIG_VERSION_CEE;
	if (dcbx_info->operational.ieee)
		p_hwfn->p_dcbx_info->set.ver_num |= DCBX_CONFIG_VERSION_IEEE;
	if (dcbx_info->operational.local)
		p_hwfn->p_dcbx_info->set.ver_num |= DCBX_CONFIG_VERSION_STATIC;

	p_hwfn->p_dcbx_info->set.enabled = dcbx_info->operational.enabled;
	OSAL_MEMCPY(&p_hwfn->p_dcbx_info->set.dscp,
		    &p_hwfn->p_dcbx_info->get.dscp,
		    sizeof(struct ecore_dcbx_dscp_params));
	OSAL_MEMCPY(&p_hwfn->p_dcbx_info->set.config.params,
		    &dcbx_info->operational.params,
		    sizeof(p_hwfn->p_dcbx_info->set.config.params));
	p_hwfn->p_dcbx_info->set.config.valid = true;

	OSAL_MEMCPY(params, &p_hwfn->p_dcbx_info->set,
		    sizeof(struct ecore_dcbx_set));

	OSAL_FREE(p_hwfn->p_dev, dcbx_info);

	return ECORE_SUCCESS;
}
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
struct ecore_hwfn {int b_int_enabled; } ;
struct ecore_hw_init_params {scalar_t__ p_tunn; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ecore_vf_pf_tunnel_param_update (struct ecore_hwfn*,scalar_t__) ; 
 int /*<<< orphan*/  ecore_vf_set_vf_start_tunn_update_param (scalar_t__) ; 

__attribute__((used)) static enum _ecore_status_t ecore_vf_start(struct ecore_hwfn *p_hwfn,
				    struct ecore_hw_init_params *p_params)
{
	if (p_params->p_tunn) {
		ecore_vf_set_vf_start_tunn_update_param(p_params->p_tunn);
		ecore_vf_pf_tunnel_param_update(p_hwfn, p_params->p_tunn);
	}

	p_hwfn->b_int_enabled = 1;

	return ECORE_SUCCESS;
}
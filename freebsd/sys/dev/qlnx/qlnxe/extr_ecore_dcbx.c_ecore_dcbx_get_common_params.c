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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_hwfn {int dummy; } ;
struct ecore_dcbx_params {int dummy; } ;
struct dcbx_ets_feature {int dummy; } ;
struct dcbx_app_priority_feature {int dummy; } ;
struct dcbx_app_priority_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecore_dcbx_get_app_data (struct ecore_hwfn*,struct dcbx_app_priority_feature*,struct dcbx_app_priority_entry*,struct ecore_dcbx_params*,int) ; 
 int /*<<< orphan*/  ecore_dcbx_get_ets_data (struct ecore_hwfn*,struct dcbx_ets_feature*,struct ecore_dcbx_params*) ; 
 int /*<<< orphan*/  ecore_dcbx_get_pfc_data (struct ecore_hwfn*,int /*<<< orphan*/ ,struct ecore_dcbx_params*) ; 

__attribute__((used)) static void
ecore_dcbx_get_common_params(struct ecore_hwfn *p_hwfn,
			     struct dcbx_app_priority_feature *p_app,
			     struct dcbx_app_priority_entry *p_tbl,
			     struct dcbx_ets_feature *p_ets,
			     u32 pfc, struct ecore_dcbx_params *p_params,
			     bool ieee)
{
	ecore_dcbx_get_app_data(p_hwfn, p_app, p_tbl, p_params, ieee);
	ecore_dcbx_get_ets_data(p_hwfn, p_ets, p_params);
	ecore_dcbx_get_pfc_data(p_hwfn, pfc, p_params);
}
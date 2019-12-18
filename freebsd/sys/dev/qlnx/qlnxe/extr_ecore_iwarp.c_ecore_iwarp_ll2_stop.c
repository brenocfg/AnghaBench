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
struct ecore_iwarp_info {scalar_t__ ll2_syn_handle; scalar_t__ ll2_ooo_handle; scalar_t__ ll2_mpa_handle; int /*<<< orphan*/  mac_addr; } ;
struct ecore_hwfn {TYPE_1__* p_rdma_info; int /*<<< orphan*/  p_dev; } ;
struct TYPE_2__ {struct ecore_iwarp_info iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*) ; 
 scalar_t__ ECORE_IWARP_HANDLE_INVAL ; 
 int /*<<< orphan*/  ecore_ll2_release_connection (struct ecore_hwfn*,scalar_t__) ; 
 int ecore_ll2_terminate_connection (struct ecore_hwfn*,scalar_t__) ; 
 int /*<<< orphan*/  ecore_llh_remove_mac_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ecore_iwarp_ll2_stop(struct ecore_hwfn *p_hwfn)
{
	struct ecore_iwarp_info *iwarp_info = &p_hwfn->p_rdma_info->iwarp;
	int rc = 0;

	if (iwarp_info->ll2_syn_handle != ECORE_IWARP_HANDLE_INVAL) {

		rc = ecore_ll2_terminate_connection(p_hwfn,
						    iwarp_info->ll2_syn_handle);
		if (rc)
			DP_INFO(p_hwfn, "Failed to terminate syn connection\n");

		ecore_ll2_release_connection(p_hwfn,
					     iwarp_info->ll2_syn_handle);
		iwarp_info->ll2_syn_handle = ECORE_IWARP_HANDLE_INVAL;
	}

	if (iwarp_info->ll2_ooo_handle != ECORE_IWARP_HANDLE_INVAL) {
		rc = ecore_ll2_terminate_connection(p_hwfn,
						    iwarp_info->ll2_ooo_handle);
		if (rc)
			DP_INFO(p_hwfn, "Failed to terminate ooo connection\n");

		ecore_ll2_release_connection(p_hwfn,
					     iwarp_info->ll2_ooo_handle);
		iwarp_info->ll2_ooo_handle = ECORE_IWARP_HANDLE_INVAL;
	}

	if (iwarp_info->ll2_mpa_handle != ECORE_IWARP_HANDLE_INVAL) {
		rc = ecore_ll2_terminate_connection(p_hwfn,
						    iwarp_info->ll2_mpa_handle);
		if (rc)
			DP_INFO(p_hwfn, "Failed to terminate mpa connection\n");

		ecore_ll2_release_connection(p_hwfn,
					     iwarp_info->ll2_mpa_handle);
		iwarp_info->ll2_mpa_handle = ECORE_IWARP_HANDLE_INVAL;
	}

	ecore_llh_remove_mac_filter(p_hwfn->p_dev, 0,
				    p_hwfn->p_rdma_info->iwarp.mac_addr);

	return rc;
}
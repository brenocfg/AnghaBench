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
struct ecore_vf_info {int dummy; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_SUCCESS ; 
 int ecore_iov_vf_flr_poll_dorq (struct ecore_hwfn*,struct ecore_vf_info*,struct ecore_ptt*) ; 
 int ecore_iov_vf_flr_poll_pbf (struct ecore_hwfn*,struct ecore_vf_info*,struct ecore_ptt*) ; 

__attribute__((used)) static enum _ecore_status_t ecore_iov_vf_flr_poll(struct ecore_hwfn *p_hwfn,
						  struct ecore_vf_info *p_vf,
						  struct ecore_ptt *p_ptt)
{
	enum _ecore_status_t rc;

	/* TODO - add SRC and TM polling once we add storage IOV */

	rc = ecore_iov_vf_flr_poll_dorq(p_hwfn, p_vf, p_ptt);
	if (rc)
		return rc;

	rc = ecore_iov_vf_flr_poll_pbf(p_hwfn, p_vf, p_ptt);
	if (rc)
		return rc;

	return ECORE_SUCCESS;
}
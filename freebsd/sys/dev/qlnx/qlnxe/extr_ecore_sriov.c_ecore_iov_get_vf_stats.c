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
typedef  int /*<<< orphan*/  u16 ;
struct ecore_vf_info {scalar_t__ state; scalar_t__ abs_vf_id; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct ecore_eth_stats {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 scalar_t__ VF_ENABLED ; 
 int /*<<< orphan*/  __ecore_get_vport_stats (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_eth_stats*,scalar_t__,int) ; 
 struct ecore_vf_info* ecore_iov_get_vf_info (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 

enum _ecore_status_t ecore_iov_get_vf_stats(struct ecore_hwfn *p_hwfn,
					    struct ecore_ptt *p_ptt,
					    int vfid,
					    struct ecore_eth_stats *p_stats)
{
	struct ecore_vf_info *vf;

	vf = ecore_iov_get_vf_info(p_hwfn, (u16)vfid, true);
	if (!vf)
		return ECORE_INVAL;

	if (vf->state != VF_ENABLED)
		return ECORE_INVAL;

	__ecore_get_vport_stats(p_hwfn, p_ptt, p_stats,
				vf->abs_vf_id + 0x10, false);

	return ECORE_SUCCESS;
}
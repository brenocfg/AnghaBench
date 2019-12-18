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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
union ecore_llh_filter {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct ecore_dev {int /*<<< orphan*/  mf_bits; } ;
typedef  int /*<<< orphan*/  filter ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_dev*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ecore_hwfn* ECORE_LEADING_HWFN (struct ecore_dev*) ; 
 int /*<<< orphan*/  ECORE_MF_LLH_MAC_CLSS ; 
 int /*<<< orphan*/  ECORE_MSG_SP ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  OSAL_MEMCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (union ecore_llh_filter*,int) ; 
 struct ecore_ptt* OSAL_NULL ; 
 int /*<<< orphan*/  OSAL_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_abs_ppfid (struct ecore_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_llh_remove_filter (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecore_llh_shadow_remove_filter (struct ecore_dev*,int /*<<< orphan*/ ,union ecore_llh_filter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 

void ecore_llh_remove_mac_filter(struct ecore_dev *p_dev, u8 ppfid,
				 u8 mac_addr[ETH_ALEN])
{
	struct ecore_hwfn *p_hwfn = ECORE_LEADING_HWFN(p_dev);
	struct ecore_ptt *p_ptt = ecore_ptt_acquire(p_hwfn);
	union ecore_llh_filter filter;
	u8 filter_idx, abs_ppfid;
	enum _ecore_status_t rc = ECORE_SUCCESS;
	u32 ref_cnt;

	if (p_ptt == OSAL_NULL)
		return;

	if (!OSAL_TEST_BIT(ECORE_MF_LLH_MAC_CLSS, &p_dev->mf_bits))
		goto out;

	OSAL_MEM_ZERO(&filter, sizeof(filter));
	OSAL_MEMCPY(filter.mac.addr, mac_addr, ETH_ALEN);
	rc = ecore_llh_shadow_remove_filter(p_dev, ppfid, &filter, &filter_idx,
					    &ref_cnt);
	if (rc != ECORE_SUCCESS)
		goto err;

	rc = ecore_abs_ppfid(p_dev, ppfid, &abs_ppfid);
	if (rc != ECORE_SUCCESS)
		goto err;

	/* Remove from the LLH in case the filter is not in use */
	if (!ref_cnt) {
		rc = ecore_llh_remove_filter(p_hwfn, p_ptt, abs_ppfid,
					     filter_idx);
		if (rc != ECORE_SUCCESS)
			goto err;
	}

	DP_VERBOSE(p_dev, ECORE_MSG_SP,
		   "LLH: Removed MAC filter [%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx] from ppfid %hhd [abs %hhd] at idx %hhd [ref_cnt %d]\n",
		   mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3],
		   mac_addr[4], mac_addr[5], ppfid, abs_ppfid, filter_idx,
		   ref_cnt);

	goto out;

err:
	DP_NOTICE(p_dev, false,
		  "LLH: Failed to remove MAC filter [%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx] from ppfid %hhd\n",
		  mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3],
		  mac_addr[4], mac_addr[5], ppfid);
out:
	ecore_ptt_release(p_hwfn, p_ptt);
}
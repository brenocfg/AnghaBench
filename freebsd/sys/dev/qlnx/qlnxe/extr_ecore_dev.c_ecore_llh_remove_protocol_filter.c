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
struct TYPE_2__ {int type; void* dest_port; void* source_port_or_eth_type; } ;
union ecore_llh_filter {TYPE_1__ protocol; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  void* u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct ecore_dev {int /*<<< orphan*/  mf_bits; } ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  filter ;
typedef  enum ecore_llh_prot_filter_type_t { ____Placeholder_ecore_llh_prot_filter_type_t } ecore_llh_prot_filter_type_t ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_dev*,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ecore_hwfn* ECORE_LEADING_HWFN (struct ecore_dev*) ; 
 int /*<<< orphan*/  ECORE_MF_LLH_PROTO_CLSS ; 
 int /*<<< orphan*/  ECORE_MSG_SP ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (union ecore_llh_filter*,int) ; 
 struct ecore_ptt* OSAL_NULL ; 
 int /*<<< orphan*/  OSAL_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_abs_ppfid (struct ecore_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_llh_protocol_filter_stringify (struct ecore_dev*,int,void*,void*,int /*<<< orphan*/ *,int) ; 
 int ecore_llh_remove_filter (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecore_llh_shadow_remove_filter (struct ecore_dev*,int /*<<< orphan*/ ,union ecore_llh_filter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 

void ecore_llh_remove_protocol_filter(struct ecore_dev *p_dev, u8 ppfid,
				      enum ecore_llh_prot_filter_type_t type,
				      u16 source_port_or_eth_type,
				      u16 dest_port)
{
	struct ecore_hwfn *p_hwfn = ECORE_LEADING_HWFN(p_dev);
	struct ecore_ptt *p_ptt = ecore_ptt_acquire(p_hwfn);
	u8 filter_idx, abs_ppfid, str[32];
	union ecore_llh_filter filter;
	enum _ecore_status_t rc = ECORE_SUCCESS;
	u32 ref_cnt;

	if (p_ptt == OSAL_NULL)
		return;

	if (!OSAL_TEST_BIT(ECORE_MF_LLH_PROTO_CLSS, &p_dev->mf_bits))
		goto out;

	rc = ecore_llh_protocol_filter_stringify(p_dev, type,
						 source_port_or_eth_type,
						 dest_port, str, sizeof(str));
	if (rc != ECORE_SUCCESS)
		goto err;

	OSAL_MEM_ZERO(&filter, sizeof(filter));
	filter.protocol.type = type;
	filter.protocol.source_port_or_eth_type = source_port_or_eth_type;
	filter.protocol.dest_port = dest_port;
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
		   "LLH: Removed protocol filter [%s] from ppfid %hhd [abs %hhd] at idx %hhd [ref_cnt %d]\n",
		   str, ppfid, abs_ppfid, filter_idx, ref_cnt);

	goto out;

err:
	DP_NOTICE(p_dev, false,
		  "LLH: Failed to remove protocol filter [%s] from ppfid %hhd\n",
		  str, ppfid);
out:
	ecore_ptt_release(p_hwfn, p_ptt);
}
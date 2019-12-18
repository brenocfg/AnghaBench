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
typedef  size_t u8 ;
struct ecore_ptt {int dummy; } ;
struct ecore_ll2_stats {int dummy; } ;
struct TYPE_2__ {scalar_t__ gsi_enable; } ;
struct ecore_ll2_info {scalar_t__ tx_stats_en; TYPE_1__ input; } ;
struct ecore_hwfn {struct ecore_ll2_info* p_ll2_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*) ; 
 int ECORE_INVAL ; 
 size_t ECORE_MAX_NUM_OF_LL2_CONNECTIONS ; 
 int ECORE_SUCCESS ; 
 struct ecore_ll2_info* OSAL_NULL ; 
 int /*<<< orphan*/  _ecore_ll2_get_port_stats (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_ll2_stats*) ; 
 int /*<<< orphan*/  _ecore_ll2_get_pstats (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_ll2_info*,struct ecore_ll2_stats*) ; 
 int /*<<< orphan*/  _ecore_ll2_get_tstats (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_ll2_info*,struct ecore_ll2_stats*) ; 
 int /*<<< orphan*/  _ecore_ll2_get_ustats (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_ll2_info*,struct ecore_ll2_stats*) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 

enum _ecore_status_t __ecore_ll2_get_stats(void *cxt,
					   u8 connection_handle,
					   struct ecore_ll2_stats *p_stats)
{
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)cxt;
	struct ecore_ll2_info *p_ll2_conn = OSAL_NULL;
	struct ecore_ptt *p_ptt;

	if ((connection_handle >= ECORE_MAX_NUM_OF_LL2_CONNECTIONS) ||
	    !p_hwfn->p_ll2_info) {
		return ECORE_INVAL;
	}

	p_ll2_conn = &p_hwfn->p_ll2_info[connection_handle];

	p_ptt = ecore_ptt_acquire(p_hwfn);
	if (!p_ptt) {
		DP_ERR(p_hwfn, "Failed to acquire ptt\n");
		return ECORE_INVAL;
	}

	if (p_ll2_conn->input.gsi_enable)
		_ecore_ll2_get_port_stats(p_hwfn, p_ptt, p_stats);

	_ecore_ll2_get_tstats(p_hwfn, p_ptt, p_ll2_conn, p_stats);

	_ecore_ll2_get_ustats(p_hwfn, p_ptt, p_ll2_conn, p_stats);

	if (p_ll2_conn->tx_stats_en)
		_ecore_ll2_get_pstats(p_hwfn, p_ptt, p_ll2_conn, p_stats);

	ecore_ptt_release(p_hwfn, p_ptt);

	return ECORE_SUCCESS;
}
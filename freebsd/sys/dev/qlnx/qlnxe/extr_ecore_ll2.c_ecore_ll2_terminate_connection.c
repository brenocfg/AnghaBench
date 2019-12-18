#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_3__ {scalar_t__ conn_type; } ;
struct ecore_ll2_info {TYPE_1__ input; } ;
struct ecore_hwfn {TYPE_2__* p_dev; int /*<<< orphan*/  p_ooo_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  mf_bits; } ;

/* Variables and functions */
 int ECORE_AGAIN ; 
 int ECORE_INVAL ; 
 scalar_t__ ECORE_LL2_RX_REGISTERED (struct ecore_ll2_info*) ; 
 scalar_t__ ECORE_LL2_TX_REGISTERED (struct ecore_ll2_info*) ; 
 scalar_t__ ECORE_LL2_TYPE_FCOE ; 
 scalar_t__ ECORE_LL2_TYPE_OOO ; 
 int /*<<< orphan*/  ECORE_LLH_FILTER_ETHERTYPE ; 
 int /*<<< orphan*/  ECORE_MF_UFP_SPECIFIC ; 
 int ECORE_NOTIMPL ; 
 int ECORE_SUCCESS ; 
 struct ecore_ll2_info* OSAL_NULL ; 
 int /*<<< orphan*/  OSAL_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ecore_ll2_info* ecore_ll2_handle_sanity_lock (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_ll2_rxq_flush (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_ll2_txq_flush (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_llh_remove_protocol_filter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_ooo_release_all_isles (int /*<<< orphan*/ ) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int ecore_sp_ll2_rx_queue_stop (struct ecore_hwfn*,struct ecore_ll2_info*) ; 
 int ecore_sp_ll2_tx_queue_stop (struct ecore_hwfn*,struct ecore_ll2_info*) ; 

enum _ecore_status_t ecore_ll2_terminate_connection(void *cxt,
						    u8 connection_handle)
{
	struct ecore_hwfn *p_hwfn = (struct ecore_hwfn *)cxt;
	struct ecore_ll2_info *p_ll2_conn = OSAL_NULL;
	enum _ecore_status_t rc = ECORE_NOTIMPL;
	struct ecore_ptt *p_ptt;

	p_ptt = ecore_ptt_acquire(p_hwfn);
	if (!p_ptt)
		return ECORE_AGAIN;

	p_ll2_conn = ecore_ll2_handle_sanity_lock(p_hwfn, connection_handle);
	if (p_ll2_conn == OSAL_NULL) {
		rc = ECORE_INVAL;
		goto out;
	}

	/* Stop Tx & Rx of connection, if needed */
	if (ECORE_LL2_TX_REGISTERED(p_ll2_conn)) {
		rc = ecore_sp_ll2_tx_queue_stop(p_hwfn, p_ll2_conn);
		if (rc != ECORE_SUCCESS)
			goto out;
		ecore_ll2_txq_flush(p_hwfn, connection_handle);
	}

	if (ECORE_LL2_RX_REGISTERED(p_ll2_conn)) {
		rc = ecore_sp_ll2_rx_queue_stop(p_hwfn, p_ll2_conn);
		if (rc)
			goto out;
		ecore_ll2_rxq_flush(p_hwfn, connection_handle);
	}

	if (p_ll2_conn->input.conn_type == ECORE_LL2_TYPE_OOO)
		ecore_ooo_release_all_isles(p_hwfn->p_ooo_info);

	if (p_ll2_conn->input.conn_type == ECORE_LL2_TYPE_FCOE) {
		if (!OSAL_TEST_BIT(ECORE_MF_UFP_SPECIFIC,
				   &p_hwfn->p_dev->mf_bits))
			ecore_llh_remove_protocol_filter(p_hwfn->p_dev, 0,
							 ECORE_LLH_FILTER_ETHERTYPE,
							 0x8906, 0);
		ecore_llh_remove_protocol_filter(p_hwfn->p_dev, 0,
						 ECORE_LLH_FILTER_ETHERTYPE,
						 0x8914, 0);
	}

out:
	ecore_ptt_release(p_hwfn, p_ptt);

	return rc;
}
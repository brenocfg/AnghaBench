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
struct eth_slow_path_rx_cqe {int /*<<< orphan*/  ramrod_cmd_id; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int ecore_cqe_completion (struct ecore_hwfn*,struct eth_slow_path_rx_cqe*,int /*<<< orphan*/ ) ; 

enum _ecore_status_t ecore_eth_cqe_completion(struct ecore_hwfn *p_hwfn,
					      struct eth_slow_path_rx_cqe *cqe)
{
	enum _ecore_status_t rc;

	rc = ecore_cqe_completion(p_hwfn, cqe, PROTOCOLID_ETH);
	if (rc) {
		DP_NOTICE(p_hwfn, true,
			  "Failed to handle RXQ CQE [cmd 0x%02x]\n",
			  cqe->ramrod_cmd_id);
	}

	return rc;
}
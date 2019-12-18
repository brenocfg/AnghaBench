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
struct eth_slow_path_rx_cqe {int /*<<< orphan*/  echo; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int OSAL_VF_CQE_COMPLETION (struct ecore_hwfn*,struct eth_slow_path_rx_cqe*,int) ; 
 int ecore_spq_completion (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t ecore_cqe_completion(struct ecore_hwfn *p_hwfn,
						 struct eth_slow_path_rx_cqe *cqe,
						 enum protocol_type protocol)
{
	if (IS_VF(p_hwfn->p_dev))
		return OSAL_VF_CQE_COMPLETION(p_hwfn, cqe, protocol);

	/* @@@tmp - it's possible we'll eventually want to handle some
	 * actual commands that can arrive here, but for now this is only
	 * used to complete the ramrod using the echo value on the cqe
	 */
	return ecore_spq_completion(p_hwfn, cqe->echo, 0, OSAL_NULL);
}
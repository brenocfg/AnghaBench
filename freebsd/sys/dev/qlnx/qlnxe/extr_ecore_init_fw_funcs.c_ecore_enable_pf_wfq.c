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
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 scalar_t__ QM_BYPASS_EN ; 
 int /*<<< orphan*/  QM_REG_AFULLQMBYPTHRPFWFQ_RT_OFFSET ; 
 int /*<<< orphan*/  QM_REG_WFQPFENABLE_RT_OFFSET ; 
 int QM_WFQ_UPPER_BOUND ; 
 int /*<<< orphan*/  STORE_RT_REG (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ecore_enable_pf_wfq(struct ecore_hwfn *p_hwfn,
								bool pf_wfq_en)
{
	STORE_RT_REG(p_hwfn, QM_REG_WFQPFENABLE_RT_OFFSET, pf_wfq_en ? 1 : 0);

	/* Set credit threshold for QM bypass flow */
	if (pf_wfq_en && QM_BYPASS_EN)
		STORE_RT_REG(p_hwfn, QM_REG_AFULLQMBYPTHRPFWFQ_RT_OFFSET, QM_WFQ_UPPER_BOUND);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_5__ {TYPE_1__ mac; int /*<<< orphan*/ * back; } ;
struct adapter {int ims; int link_mask; TYPE_2__ hw; int /*<<< orphan*/  ctx; int /*<<< orphan*/  rx_overruns; int /*<<< orphan*/  link_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EIMS ; 
 int /*<<< orphan*/  E1000_ICR ; 
 int E1000_ICR_LSC ; 
 int E1000_ICR_RXO ; 
 int E1000_ICR_RXSEQ ; 
 int /*<<< orphan*/  E1000_ICS ; 
 int /*<<< orphan*/  E1000_IMS ; 
 int E1000_IMS_LSC ; 
 int E1000_READ_REG (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int EM_MSIX_LINK ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_82574 ; 
 int /*<<< orphan*/  em_handle_link (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
em_msix_link(void *arg)
{
	struct adapter *adapter = arg;
	u32 reg_icr;

	++adapter->link_irq;
	MPASS(adapter->hw.back != NULL);
	reg_icr = E1000_READ_REG(&adapter->hw, E1000_ICR);

	if (reg_icr & E1000_ICR_RXO)
		adapter->rx_overruns++;

	if (reg_icr & (E1000_ICR_RXSEQ | E1000_ICR_LSC)) {
		em_handle_link(adapter->ctx);
	} else if (adapter->hw.mac.type == e1000_82574) {
		/* Only re-arm 82574 if em_if_update_admin_status() won't. */
		E1000_WRITE_REG(&adapter->hw, E1000_IMS, EM_MSIX_LINK |
		    E1000_IMS_LSC);
	}

	if (adapter->hw.mac.type == e1000_82574) {
		/*
		 * Because we must read the ICR for this interrupt it may
		 * clear other causes using autoclear, for this reason we
		 * simply create a soft interrupt for all these vectors.
		 */
		if (reg_icr)
			E1000_WRITE_REG(&adapter->hw, E1000_ICS, adapter->ims);
	} else {
		/* Re-arm unconditionally */
		E1000_WRITE_REG(&adapter->hw, E1000_IMS, E1000_IMS_LSC);
		E1000_WRITE_REG(&adapter->hw, E1000_EIMS, adapter->link_mask);
	}

	return (FILTER_HANDLED);
}
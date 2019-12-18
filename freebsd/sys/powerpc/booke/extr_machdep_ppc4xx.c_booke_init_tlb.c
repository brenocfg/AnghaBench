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
typedef  int /*<<< orphan*/  vm_paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  APM86XXX_AHB_PA ; 
 scalar_t__ APM86XXX_AHB_VA ; 
 int /*<<< orphan*/  APM86XXX_CSR_PA ; 
 scalar_t__ APM86XXX_CSR_VA ; 
 int /*<<< orphan*/  APM86XXX_DEEP_SLEEP_PA ; 
 scalar_t__ APM86XXX_DEEP_SLEEP_VA ; 
 int /*<<< orphan*/  APM86XXX_MBOX_PA ; 
 scalar_t__ APM86XXX_MBOX_VA ; 
 int /*<<< orphan*/  APM86XXX_PRIMARY_FABRIC_PA ; 
 scalar_t__ APM86XXX_PRIMARY_FABRIC_VA ; 
 int /*<<< orphan*/  OCP_ADDR_WORDHI (int /*<<< orphan*/ ) ; 
 scalar_t__ OCP_ADDR_WORDLO (int /*<<< orphan*/ ) ; 
 int TLB_G ; 
 int TLB_I ; 
 int TLB_SIZE_16M ; 
 int TLB_SIZE_4K ; 
 int TLB_SR ; 
 int TLB_SW ; 
 int TLB_SX ; 
 int TLB_UR ; 
 int TLB_UW ; 
 int TLB_UX ; 
 int TLB_VALID ; 
 int /*<<< orphan*/  tlb_map (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int) ; 

void
booke_init_tlb(vm_paddr_t fdt_immr_pa)
{

	/* Map register space */
	tlb_map(APM86XXX_DEEP_SLEEP_VA,
	    OCP_ADDR_WORDLO(APM86XXX_DEEP_SLEEP_PA),
	    OCP_ADDR_WORDHI(APM86XXX_DEEP_SLEEP_PA), TLB_VALID | TLB_SIZE_16M,
	    TLB_SW | TLB_SR | TLB_I | TLB_G);

	tlb_map(APM86XXX_CSR_VA, OCP_ADDR_WORDLO(APM86XXX_CSR_PA),
	    OCP_ADDR_WORDHI(APM86XXX_CSR_PA), TLB_VALID | TLB_SIZE_16M,
	    TLB_SW | TLB_SR | TLB_I | TLB_G);

	tlb_map(APM86XXX_PRIMARY_FABRIC_VA,
	    OCP_ADDR_WORDLO(APM86XXX_PRIMARY_FABRIC_PA),
	    OCP_ADDR_WORDHI(APM86XXX_PRIMARY_FABRIC_PA),
	    TLB_VALID | TLB_SIZE_16M,
	    TLB_SW | TLB_SR | TLB_I | TLB_G);

	tlb_map(APM86XXX_AHB_VA, OCP_ADDR_WORDLO(APM86XXX_AHB_PA),
	    OCP_ADDR_WORDHI(APM86XXX_AHB_PA),
	    TLB_VALID | TLB_SIZE_16M,
	    TLB_SW | TLB_SR | TLB_I | TLB_G);

	/* Map MailBox space */
	tlb_map(APM86XXX_MBOX_VA, OCP_ADDR_WORDLO(APM86XXX_MBOX_PA),
	    OCP_ADDR_WORDHI(APM86XXX_MBOX_PA),
	    TLB_VALID | TLB_SIZE_4K,
	    TLB_UX | TLB_UW | TLB_UR |
	    TLB_SX | TLB_SW | TLB_SR |
	    TLB_I | TLB_G);

	tlb_map(APM86XXX_MBOX_VA + 0x1000,
	    OCP_ADDR_WORDLO(APM86XXX_MBOX_PA) + 0x1000,
	    OCP_ADDR_WORDHI(APM86XXX_MBOX_PA),
	    TLB_VALID | TLB_SIZE_4K,
	    TLB_UX | TLB_UW | TLB_UR |
	    TLB_SX | TLB_SW | TLB_SR |
	    TLB_I | TLB_G);

	tlb_map(APM86XXX_MBOX_VA + 0x2000,
	    OCP_ADDR_WORDLO(APM86XXX_MBOX_PA)+ 0x2000,
	    OCP_ADDR_WORDHI(APM86XXX_MBOX_PA),
	    TLB_VALID | TLB_SIZE_4K,
	    TLB_UX | TLB_UW | TLB_UR |
	    TLB_SX | TLB_SW | TLB_SR |
	    TLB_I | TLB_G);
}
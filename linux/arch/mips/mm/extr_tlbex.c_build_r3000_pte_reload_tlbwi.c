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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  C0_ENTRYLO0 ; 
 int /*<<< orphan*/  C0_EPC ; 
 int /*<<< orphan*/  uasm_i_jr (int /*<<< orphan*/ **,unsigned int) ; 
 int /*<<< orphan*/  uasm_i_mfc0 (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_mtc0 (int /*<<< orphan*/ **,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uasm_i_rfe (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uasm_i_tlbwi (int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
build_r3000_pte_reload_tlbwi(u32 **p, unsigned int pte, unsigned int tmp)
{
	uasm_i_mtc0(p, pte, C0_ENTRYLO0); /* cp0 delay */
	uasm_i_mfc0(p, tmp, C0_EPC); /* cp0 delay */
	uasm_i_tlbwi(p);
	uasm_i_jr(p, tmp);
	uasm_i_rfe(p); /* branch delay */
}
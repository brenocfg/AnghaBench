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

/* Variables and functions */
 int /*<<< orphan*/  modify_instruction_site (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  patch__tlb_44x_hwater_D ; 
 int /*<<< orphan*/  patch__tlb_44x_hwater_I ; 
 int /*<<< orphan*/  tlb_44x_hwater ; 

__attribute__((used)) static void ppc44x_update_tlb_hwater(void)
{
	/* The TLB miss handlers hard codes the watermark in a cmpli
	 * instruction to improve performances rather than loading it
	 * from the global variable. Thus, we patch the instructions
	 * in the 2 TLB miss handlers when updating the value
	 */
	modify_instruction_site(&patch__tlb_44x_hwater_D, 0xffff, tlb_44x_hwater);
	modify_instruction_site(&patch__tlb_44x_hwater_I, 0xffff, tlb_44x_hwater);
}
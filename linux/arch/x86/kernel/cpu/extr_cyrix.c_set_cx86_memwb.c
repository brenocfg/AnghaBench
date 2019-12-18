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
 int /*<<< orphan*/  CX86_CCR2 ; 
 int X86_CR0_NW ; 
 int getCx86 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int read_cr0 () ; 
 int /*<<< orphan*/  setCx86 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_cr0 (int) ; 

__attribute__((used)) static void set_cx86_memwb(void)
{
	pr_info("Enable Memory-Write-back mode on Cyrix/NSC processor.\n");

	/* CCR2 bit 2: unlock NW bit */
	setCx86(CX86_CCR2, getCx86(CX86_CCR2) & ~0x04);
	/* set 'Not Write-through' */
	write_cr0(read_cr0() | X86_CR0_NW);
	/* CCR2 bit 2: lock NW bit and set WT1 */
	setCx86(CX86_CCR2, getCx86(CX86_CCR2) | 0x14);
}
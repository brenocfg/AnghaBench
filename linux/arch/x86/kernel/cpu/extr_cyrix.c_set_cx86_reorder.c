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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CX86_CCR3 ; 
 int /*<<< orphan*/  CX86_PCR0 ; 
 int getCx86 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  setCx86 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_cx86_reorder(void)
{
	u8 ccr3;

	pr_info("Enable Memory access reorder on Cyrix/NSC processor.\n");
	ccr3 = getCx86(CX86_CCR3);
	setCx86(CX86_CCR3, (ccr3 & 0x0f) | 0x10); /* enable MAPEN */

	/* Load/Store Serialize to mem access disable (=reorder it) */
	setCx86(CX86_PCR0, getCx86(CX86_PCR0) & ~0x80);
	/* set load/store serialize from 1GB to 4GB */
	ccr3 |= 0xe0;
	setCx86(CX86_CCR3, ccr3);
}
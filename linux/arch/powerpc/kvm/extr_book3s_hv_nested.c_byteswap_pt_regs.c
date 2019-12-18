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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned long swab64 (unsigned long) ; 

__attribute__((used)) static void byteswap_pt_regs(struct pt_regs *regs)
{
	unsigned long *addr = (unsigned long *) regs;

	for (; addr < ((unsigned long *) (regs + 1)); addr++)
		*addr = swab64(*addr);
}
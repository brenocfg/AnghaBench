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
struct mm_struct {int dummy; } ;
struct arch_uprobe {int dummy; } ;

/* Variables and functions */

int arch_uprobe_analyze_insn(struct arch_uprobe *auprobe,
			     struct mm_struct *mm, unsigned long addr)
{
	/* Any unsupported instruction?  Then return -EINVAL  */
	return 0;
}
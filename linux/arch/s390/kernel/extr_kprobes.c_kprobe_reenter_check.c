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
struct kprobe_ctlblk {int kprobe_status; } ;
struct kprobe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  KPROBE_HIT_ACTIVE 131 
#define  KPROBE_HIT_SS 130 
#define  KPROBE_HIT_SSDONE 129 
#define  KPROBE_REENTER 128 
 int /*<<< orphan*/  dump_kprobe (struct kprobe*) ; 
 int /*<<< orphan*/  kprobes_inc_nmissed_count (struct kprobe*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void kprobe_reenter_check(struct kprobe_ctlblk *kcb, struct kprobe *p)
{
	switch (kcb->kprobe_status) {
	case KPROBE_HIT_SSDONE:
	case KPROBE_HIT_ACTIVE:
		kprobes_inc_nmissed_count(p);
		break;
	case KPROBE_HIT_SS:
	case KPROBE_REENTER:
	default:
		/*
		 * A kprobe on the code path to single step an instruction
		 * is a BUG. The code path resides in the .kprobes.text
		 * section and is executed with interrupts disabled.
		 */
		pr_err("Invalid kprobe detected.\n");
		dump_kprobe(p);
		BUG();
	}
}
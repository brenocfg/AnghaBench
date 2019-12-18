#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ addr; } ;
struct TYPE_3__ {int size; } ;
struct optimized_kprobe {TYPE_2__ kp; TYPE_1__ optinsn; } ;
struct kprobe {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 struct kprobe* get_kprobe (scalar_t__) ; 
 int /*<<< orphan*/  kprobe_disabled (struct kprobe*) ; 

int arch_check_optimized_kprobe(struct optimized_kprobe *op)
{
	int i;
	struct kprobe *p;

	for (i = 1; i < op->optinsn.size; i++) {
		p = get_kprobe(op->kp.addr + i);
		if (p && !kprobe_disabled(p))
			return -EEXIST;
	}

	return 0;
}
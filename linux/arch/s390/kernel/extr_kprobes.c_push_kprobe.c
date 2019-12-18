#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  kp; } ;
struct kprobe_ctlblk {int /*<<< orphan*/  kprobe_status; TYPE_1__ prev_kprobe; } ;
struct kprobe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,struct kprobe*) ; 
 int /*<<< orphan*/  current_kprobe ; 

__attribute__((used)) static void push_kprobe(struct kprobe_ctlblk *kcb, struct kprobe *p)
{
	kcb->prev_kprobe.kp = __this_cpu_read(current_kprobe);
	kcb->prev_kprobe.status = kcb->kprobe_status;
	__this_cpu_write(current_kprobe, p);
}
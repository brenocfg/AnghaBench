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
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct kvm_pit {int /*<<< orphan*/  expired; TYPE_1__ pit_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_flush_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_pit_timer(struct kvm_pit *pit)
{
	hrtimer_cancel(&pit->pit_state.timer);
	kthread_flush_work(&pit->expired);
}
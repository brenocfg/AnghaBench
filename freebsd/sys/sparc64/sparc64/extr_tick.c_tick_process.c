#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int dummy; } ;
struct thread {int /*<<< orphan*/  td_intr_nesting_level; struct trapframe* td_intr_frame; } ;
struct TYPE_3__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ tick_et ; 

__attribute__((used)) static inline void
tick_process(struct trapframe *tf)
{
	struct trapframe *oldframe;
	struct thread *td;

	td = curthread;
	td->td_intr_nesting_level++;
	critical_enter();
	if (tick_et.et_active) {
		oldframe = td->td_intr_frame;
		td->td_intr_frame = tf;
		tick_et.et_event_cb(&tick_et, tick_et.et_arg);
		td->td_intr_frame = oldframe;
	}
	td->td_intr_nesting_level--;
	critical_exit();
}
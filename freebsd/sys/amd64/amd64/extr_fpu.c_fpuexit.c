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
struct thread {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcb_save; } ;

/* Variables and functions */
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 TYPE_1__* curpcb ; 
 scalar_t__ curthread ; 
 int /*<<< orphan*/  fpcurthread ; 
 int /*<<< orphan*/  fpusave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_emulating () ; 
 int /*<<< orphan*/  stop_emulating () ; 

void
fpuexit(struct thread *td)
{

	critical_enter();
	if (curthread == PCPU_GET(fpcurthread)) {
		stop_emulating();
		fpusave(curpcb->pcb_save);
		start_emulating();
		PCPU_SET(fpcurthread, NULL);
	}
	critical_exit();
}
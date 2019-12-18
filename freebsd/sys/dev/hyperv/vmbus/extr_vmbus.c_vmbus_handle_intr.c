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
struct vmbus_softc {int dummy; } ;
struct trapframe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * VMBUS_PCPU_GET (struct vmbus_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int curcpu ; 
 int /*<<< orphan*/  intr_cnt ; 
 struct vmbus_softc* vmbus_get_softc () ; 
 int /*<<< orphan*/  vmbus_handle_intr1 (struct vmbus_softc*,struct trapframe*,int) ; 

void
vmbus_handle_intr(struct trapframe *trap_frame)
{
	struct vmbus_softc *sc = vmbus_get_softc();
	int cpu = curcpu;

	/*
	 * Disable preemption.
	 */
	critical_enter();

	/*
	 * Do a little interrupt counting.
	 */
	(*VMBUS_PCPU_GET(sc, intr_cnt, cpu))++;

	vmbus_handle_intr1(sc, trap_frame, cpu);

	/*
	 * Enable preemption.
	 */
	critical_exit();
}
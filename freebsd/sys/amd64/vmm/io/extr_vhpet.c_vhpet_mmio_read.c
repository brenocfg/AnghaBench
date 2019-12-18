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
typedef  int uint64_t ;
struct vhpet {int config; int isr; TYPE_1__* timer; int /*<<< orphan*/  vm; } ;
struct TYPE_2__ {int cap_config; int compval; int msireg; } ;

/* Variables and functions */
 int HPET_CAPABILITIES ; 
 int HPET_CONFIG ; 
 int HPET_ISR ; 
 int HPET_MAIN_COUNTER ; 
 int HPET_TIMER_CAP_CNF (int) ; 
 int HPET_TIMER_COMPARATOR (int) ; 
 int HPET_TIMER_FSB_ADDR (int) ; 
 int HPET_TIMER_FSB_VAL (int) ; 
 int VHPET_BASE ; 
 int /*<<< orphan*/  VHPET_LOCK (struct vhpet*) ; 
 int VHPET_NUM_TIMERS ; 
 int /*<<< orphan*/  VHPET_UNLOCK (struct vhpet*) ; 
 int /*<<< orphan*/  VM_CTR2 (int /*<<< orphan*/ ,char*,int,int) ; 
 int vhpet_capabilities () ; 
 int vhpet_counter (struct vhpet*,int /*<<< orphan*/ *) ; 
 struct vhpet* vm_hpet (void*) ; 

int
vhpet_mmio_read(void *vm, int vcpuid, uint64_t gpa, uint64_t *rval, int size,
    void *arg)
{
	int i, offset;
	struct vhpet *vhpet;
	uint64_t data;

	vhpet = vm_hpet(vm);
	offset = gpa - VHPET_BASE;

	VHPET_LOCK(vhpet);

	/* Accesses to the HPET should be 4 or 8 bytes wide */
	if (size != 4 && size != 8) {
		VM_CTR2(vhpet->vm, "hpet invalid mmio read: "
		    "offset 0x%08x, size %d", offset, size);
		data = 0;
		goto done;
	}

	/* Access to the HPET should be naturally aligned to its width */
	if (offset & (size - 1)) {
		VM_CTR2(vhpet->vm, "hpet invalid mmio read: "
		    "offset 0x%08x, size %d", offset, size);
		data = 0;
		goto done;
	}

	if (offset == HPET_CAPABILITIES || offset == HPET_CAPABILITIES + 4) {
		data = vhpet_capabilities();
		goto done;	
	}

	if (offset == HPET_CONFIG || offset == HPET_CONFIG + 4) {
		data = vhpet->config;
		goto done;
	}

	if (offset == HPET_ISR || offset == HPET_ISR + 4) {
		data = vhpet->isr;
		goto done;
	}

	if (offset == HPET_MAIN_COUNTER || offset == HPET_MAIN_COUNTER + 4) {
		data = vhpet_counter(vhpet, NULL);
		goto done;
	}

	for (i = 0; i < VHPET_NUM_TIMERS; i++) {
		if (offset == HPET_TIMER_CAP_CNF(i) ||
		    offset == HPET_TIMER_CAP_CNF(i) + 4) {
			data = vhpet->timer[i].cap_config;
			break;
		}

		if (offset == HPET_TIMER_COMPARATOR(i) ||
		    offset == HPET_TIMER_COMPARATOR(i) + 4) {
			data = vhpet->timer[i].compval;
			break;
		}

		if (offset == HPET_TIMER_FSB_VAL(i) ||
		    offset == HPET_TIMER_FSB_ADDR(i)) {
			data = vhpet->timer[i].msireg;
			break;
		}
	}

	if (i >= VHPET_NUM_TIMERS)
		data = 0;
done:
	VHPET_UNLOCK(vhpet);

	if (size == 4) {
		if (offset & 0x4)
			data >>= 32;
	}
	*rval = data;
	return (0);
}
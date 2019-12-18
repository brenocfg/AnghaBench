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
typedef  int uint32_t ;
struct vhpet {int config; int isr; int countbase; TYPE_1__* timer; int /*<<< orphan*/  vm; } ;
typedef  int /*<<< orphan*/  sbintime_t ;
struct TYPE_2__ {int compval; int comprate; int cap_config; int msireg; } ;

/* Variables and functions */
 int HPET_CNF_ENABLE ; 
 int HPET_CNF_LEG_RT ; 
 int HPET_CONFIG ; 
 int HPET_ISR ; 
 int HPET_MAIN_COUNTER ; 
 int HPET_TCNF_VAL_SET ; 
 int HPET_TIMER_CAP_CNF (int) ; 
 int HPET_TIMER_COMPARATOR (int) ; 
 int HPET_TIMER_FSB_ADDR (int) ; 
 int HPET_TIMER_FSB_VAL (int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int VHPET_BASE ; 
 int /*<<< orphan*/  VHPET_LOCK (struct vhpet*) ; 
 int VHPET_NUM_TIMERS ; 
 int /*<<< orphan*/  VHPET_UNLOCK (struct vhpet*) ; 
 int /*<<< orphan*/  VM_CTR0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VM_CTR1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  VM_CTR2 (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  update_register (int*,int,int) ; 
 int vhpet_counter (struct vhpet*,int /*<<< orphan*/ *) ; 
 scalar_t__ vhpet_counter_enabled (struct vhpet*) ; 
 scalar_t__ vhpet_periodic_timer (struct vhpet*,int) ; 
 int /*<<< orphan*/  vhpet_start_counting (struct vhpet*) ; 
 int /*<<< orphan*/  vhpet_start_timer (struct vhpet*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhpet_stop_counting (struct vhpet*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhpet_timer_clear_isr (struct vhpet*,int) ; 
 int /*<<< orphan*/  vhpet_timer_update_config (struct vhpet*,int,int,int) ; 
 struct vhpet* vm_hpet (void*) ; 

int
vhpet_mmio_write(void *vm, int vcpuid, uint64_t gpa, uint64_t val, int size,
    void *arg)
{
	struct vhpet *vhpet;
	uint64_t data, mask, oldval, val64;
	uint32_t isr_clear_mask, old_compval, old_comprate, counter;
	sbintime_t now, *nowptr;
	int i, offset;

	vhpet = vm_hpet(vm);
	offset = gpa - VHPET_BASE;

	VHPET_LOCK(vhpet);

	/* Accesses to the HPET should be 4 or 8 bytes wide */
	switch (size) {
	case 8:
		mask = 0xffffffffffffffff;
		data = val;
		break;
	case 4:
		mask = 0xffffffff;
		data = val;
		if ((offset & 0x4) != 0) {
			mask <<= 32;
			data <<= 32;
		} 
		break;
	default:
		VM_CTR2(vhpet->vm, "hpet invalid mmio write: "
		    "offset 0x%08x, size %d", offset, size);
		goto done;
	}

	/* Access to the HPET should be naturally aligned to its width */
	if (offset & (size - 1)) {
		VM_CTR2(vhpet->vm, "hpet invalid mmio write: "
		    "offset 0x%08x, size %d", offset, size);
		goto done;
	}

	if (offset == HPET_CONFIG || offset == HPET_CONFIG + 4) {
		/*
		 * Get the most recent value of the counter before updating
		 * the 'config' register. If the HPET is going to be disabled
		 * then we need to update 'countbase' with the value right
		 * before it is disabled.
		 */
		nowptr = vhpet_counter_enabled(vhpet) ? &now : NULL;
		counter = vhpet_counter(vhpet, nowptr);
		oldval = vhpet->config;
		update_register(&vhpet->config, data, mask);

		/*
		 * LegacyReplacement Routing is not supported so clear the
		 * bit explicitly.
		 */
		vhpet->config &= ~HPET_CNF_LEG_RT;

		if ((oldval ^ vhpet->config) & HPET_CNF_ENABLE) {
			if (vhpet_counter_enabled(vhpet)) {
				vhpet_start_counting(vhpet);
				VM_CTR0(vhpet->vm, "hpet enabled");
			} else {
				vhpet_stop_counting(vhpet, counter, now);
				VM_CTR0(vhpet->vm, "hpet disabled");
			}
		}
		goto done;
	}

	if (offset == HPET_ISR || offset == HPET_ISR + 4) {
		isr_clear_mask = vhpet->isr & data;
		for (i = 0; i < VHPET_NUM_TIMERS; i++) {
			if ((isr_clear_mask & (1 << i)) != 0) {
				VM_CTR1(vhpet->vm, "hpet t%d isr cleared", i);
				vhpet_timer_clear_isr(vhpet, i);
			}
		}
		goto done;
	}

	if (offset == HPET_MAIN_COUNTER || offset == HPET_MAIN_COUNTER + 4) {
		/* Zero-extend the counter to 64-bits before updating it */
		val64 = vhpet_counter(vhpet, NULL);
		update_register(&val64, data, mask);
		vhpet->countbase = val64;
		if (vhpet_counter_enabled(vhpet))
			vhpet_start_counting(vhpet);
		goto done;
	}

	for (i = 0; i < VHPET_NUM_TIMERS; i++) {
		if (offset == HPET_TIMER_CAP_CNF(i) ||
		    offset == HPET_TIMER_CAP_CNF(i) + 4) {
			vhpet_timer_update_config(vhpet, i, data, mask);
			break;
		}

		if (offset == HPET_TIMER_COMPARATOR(i) ||
		    offset == HPET_TIMER_COMPARATOR(i) + 4) {
			old_compval = vhpet->timer[i].compval;
			old_comprate = vhpet->timer[i].comprate;
			if (vhpet_periodic_timer(vhpet, i)) {
				/*
				 * In periodic mode writes to the comparator
				 * change the 'compval' register only if the
				 * HPET_TCNF_VAL_SET bit is set in the config
				 * register.
				 */
				val64 = vhpet->timer[i].comprate;
				update_register(&val64, data, mask);
				vhpet->timer[i].comprate = val64;
				if ((vhpet->timer[i].cap_config &
				    HPET_TCNF_VAL_SET) != 0) {
					vhpet->timer[i].compval = val64;
				}
			} else {
				KASSERT(vhpet->timer[i].comprate == 0,
				    ("vhpet one-shot timer %d has invalid "
				    "rate %u", i, vhpet->timer[i].comprate));
				val64 = vhpet->timer[i].compval;
				update_register(&val64, data, mask);
				vhpet->timer[i].compval = val64;
			}
			vhpet->timer[i].cap_config &= ~HPET_TCNF_VAL_SET;

			if (vhpet->timer[i].compval != old_compval ||
			    vhpet->timer[i].comprate != old_comprate) {
				if (vhpet_counter_enabled(vhpet)) {
					counter = vhpet_counter(vhpet, &now);
					vhpet_start_timer(vhpet, i, counter,
					    now);
				}
			}
			break;
		}

		if (offset == HPET_TIMER_FSB_VAL(i) ||
		    offset == HPET_TIMER_FSB_ADDR(i)) {
			update_register(&vhpet->timer[i].msireg, data, mask);
			break;
		}
	}
done:
	VHPET_UNLOCK(vhpet);
	return (0);
}
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
struct vm {int dummy; } ;
struct vhpet_callout_arg {int timer_num; struct vhpet* vhpet; } ;
struct vhpet {TYPE_1__* timer; int /*<<< orphan*/  freq_sbt; int /*<<< orphan*/  mtx; struct vm* vm; } ;
struct bintime {int dummy; } ;
struct TYPE_2__ {int cap_config; int compval; struct vhpet_callout_arg arg; int /*<<< orphan*/  callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREQ2BT (int /*<<< orphan*/ ,struct bintime*) ; 
 int /*<<< orphan*/  HPET_FREQ ; 
 int HPET_TCAP_FSB_INT_DEL ; 
 int HPET_TCAP_PER_INT ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_VHPET ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int VHPET_NUM_TIMERS ; 
 int /*<<< orphan*/  bttosbt (struct bintime) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 struct vhpet* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vioapic_pincount (struct vm*) ; 

struct vhpet *
vhpet_init(struct vm *vm)
{
	int i, pincount;
	struct vhpet *vhpet;
	uint64_t allowed_irqs;
	struct vhpet_callout_arg *arg;
	struct bintime bt;

	vhpet = malloc(sizeof(struct vhpet), M_VHPET, M_WAITOK | M_ZERO);
        vhpet->vm = vm;
	mtx_init(&vhpet->mtx, "vhpet lock", NULL, MTX_DEF);

	FREQ2BT(HPET_FREQ, &bt);
	vhpet->freq_sbt = bttosbt(bt);

	pincount = vioapic_pincount(vm);
	if (pincount >= 32)
		allowed_irqs = 0xff000000;	/* irqs 24-31 */
	else if (pincount >= 20)
		allowed_irqs = 0xf << (pincount - 4);	/* 4 upper irqs */
	else
		allowed_irqs = 0;

	/*
	 * Initialize HPET timer hardware state.
	 */
	for (i = 0; i < VHPET_NUM_TIMERS; i++) {
		vhpet->timer[i].cap_config = allowed_irqs << 32;
		vhpet->timer[i].cap_config |= HPET_TCAP_PER_INT;
		vhpet->timer[i].cap_config |= HPET_TCAP_FSB_INT_DEL;

		vhpet->timer[i].compval = 0xffffffff;
		callout_init(&vhpet->timer[i].callout, 1);

		arg = &vhpet->timer[i].arg;
		arg->vhpet = vhpet;
		arg->timer_num = i;
	}

	return (vhpet);
}
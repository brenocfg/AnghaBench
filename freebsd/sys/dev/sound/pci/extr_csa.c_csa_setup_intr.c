#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sndcard_func {int func; } ;
struct resource {int dummy; } ;
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {struct resource* irq; } ;
typedef  TYPE_2__ csa_res ;
struct TYPE_6__ {void* midiintr_arg; int /*<<< orphan*/ * midiintr; void* pcmintr_arg; int /*<<< orphan*/ * pcmintr; TYPE_2__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  BA0_HICR ; 
 int /*<<< orphan*/  BA0_HISR ; 
 int EINVAL ; 
 int HICR_CHGM ; 
 int HICR_IEV ; 
 int HISR_INTENA ; 
#define  SCF_MIDI 129 
#define  SCF_PCM 128 
 int csa_readio (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_writeio (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct sndcard_func* device_get_ivars (int /*<<< orphan*/ ) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
csa_setup_intr(device_t bus, device_t child,
	       struct resource *irq, int flags,
	       driver_filter_t *filter,
	       driver_intr_t *intr, void *arg, void **cookiep)
{
	sc_p scp;
	csa_res *resp;
	struct sndcard_func *func;

	if (filter != NULL) {
		printf("ata-csa.c: we cannot use a filter here\n");
		return (EINVAL);
	}
	scp = device_get_softc(bus);
	resp = &scp->res;

	/*
	 * Look at the function code of the child to determine
	 * the appropriate hander for it.
	 */
	func = device_get_ivars(child);
	if (func == NULL || irq != resp->irq)
		return (EINVAL);

	switch (func->func) {
	case SCF_PCM:
		scp->pcmintr = intr;
		scp->pcmintr_arg = arg;
		break;

	case SCF_MIDI:
		scp->midiintr = intr;
		scp->midiintr_arg = arg;
		break;

	default:
		return (EINVAL);
	}
	*cookiep = scp;
	if ((csa_readio(resp, BA0_HISR) & HISR_INTENA) == 0)
		csa_writeio(resp, BA0_HICR, HICR_IEV | HICR_CHGM);

	return (0);
}
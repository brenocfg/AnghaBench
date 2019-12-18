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
typedef  int /*<<< orphan*/  u_int ;
struct resource {int dummy; } ;
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int* io_alloced; int irq_alloced; int* drq_alloced; struct resource** drq; struct resource* irq; struct resource** io; } ;

/* Variables and functions */
#define  SYS_RES_DRQ 130 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_IRQ 128 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource *
gusc_alloc_resource(device_t bus, device_t child, int type, int *rid,
		    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	sc_p scp;
	int *alloced, rid_max, alloced_max;
	struct resource **res;

	scp = device_get_softc(bus);
	switch (type) {
	case SYS_RES_IOPORT:
		alloced = scp->io_alloced;
		res = scp->io;
		rid_max = 2;
		alloced_max = 2; /* pcm + midi (more to include synth) */
		break;
	case SYS_RES_IRQ:
		alloced = &scp->irq_alloced;
		res = &scp->irq;
		rid_max = 0;
		alloced_max = 2; /* pcm and midi share the single irq. */
		break;
	case SYS_RES_DRQ:
		alloced = scp->drq_alloced;
		res = scp->drq;
		rid_max = 1;
		alloced_max = 1;
		break;
	default:
		return (NULL);
	}

	if (*rid > rid_max || alloced[*rid] == alloced_max)
		return (NULL);

	alloced[*rid]++;
	return (res[*rid]);
}
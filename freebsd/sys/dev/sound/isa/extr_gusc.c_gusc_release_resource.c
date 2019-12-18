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
struct resource {int dummy; } ;
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int* io_alloced; int irq_alloced; int* drq_alloced; } ;

/* Variables and functions */
#define  SYS_RES_DRQ 130 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_IRQ 128 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gusc_release_resource(device_t bus, device_t child, int type, int rid,
			struct resource *r)
{
	sc_p scp;
	int *alloced, rid_max;

	scp = device_get_softc(bus);
	switch (type) {
	case SYS_RES_IOPORT:
		alloced = scp->io_alloced;
		rid_max = 2;
		break;
	case SYS_RES_IRQ:
		alloced = &scp->irq_alloced;
		rid_max = 0;
		break;
	case SYS_RES_DRQ:
		alloced = scp->drq_alloced;
		rid_max = 1;
		break;
	default:
		return (1);
	}

	if (rid > rid_max || alloced[rid] == 0)
		return (1);

	alloced[rid]--;
	return (0);
}
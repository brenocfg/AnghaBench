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
typedef  int /*<<< orphan*/  u_int ;
struct sbc_softc {int* io_alloced; int* drq_alloced; int* irq_alloced; struct resource** irq; struct resource** drq; struct resource** io; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRQ_MAX ; 
 int INTR_MAX ; 
 int /*<<< orphan*/  IO_MAX ; 
 int /*<<< orphan*/  IRQ_MAX ; 
#define  SYS_RES_DRQ 130 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_IRQ 128 
 struct sbc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource *
sbc_alloc_resource(device_t bus, device_t child, int type, int *rid,
		   rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct sbc_softc *scp;
	int *alloced, rid_max, alloced_max;
	struct resource **res;

	scp = device_get_softc(bus);
	switch (type) {
	case SYS_RES_IOPORT:
		alloced = scp->io_alloced;
		res = scp->io;
		rid_max = IO_MAX - 1;
		alloced_max = 1;
		break;
	case SYS_RES_DRQ:
		alloced = scp->drq_alloced;
		res = scp->drq;
		rid_max = DRQ_MAX - 1;
		alloced_max = 1;
		break;
	case SYS_RES_IRQ:
		alloced = scp->irq_alloced;
		res = scp->irq;
		rid_max = IRQ_MAX - 1;
		alloced_max = INTR_MAX; /* pcm and mpu may share the irq. */
		break;
	default:
		return (NULL);
	}

	if (*rid > rid_max || alloced[*rid] == alloced_max)
		return (NULL);

	alloced[*rid]++;
	return (res[*rid]);
}
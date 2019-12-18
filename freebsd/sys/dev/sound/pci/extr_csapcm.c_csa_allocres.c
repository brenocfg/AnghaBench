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
struct TYPE_2__ {int /*<<< orphan*/ * irq; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/ * mem; int /*<<< orphan*/  mem_rid; int /*<<< orphan*/ * io; int /*<<< orphan*/  io_rid; } ;
struct csa_info {int /*<<< orphan*/  parent_dmat; TYPE_1__ res; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  TYPE_1__ csa_res ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  CS461x_BUFFSIZE ; 
 int /*<<< orphan*/  Giant ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 

__attribute__((used)) static int
csa_allocres(struct csa_info *csa, device_t dev)
{
	csa_res *resp;

	resp = &csa->res;
	if (resp->io == NULL) {
		resp->io = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
			&resp->io_rid, RF_ACTIVE);
		if (resp->io == NULL)
			return (1);
	}
	if (resp->mem == NULL) {
		resp->mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
			&resp->mem_rid, RF_ACTIVE);
		if (resp->mem == NULL)
			return (1);
	}
	if (resp->irq == NULL) {
		resp->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ,
			&resp->irq_rid, RF_ACTIVE | RF_SHAREABLE);
		if (resp->irq == NULL)
			return (1);
	}
	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(dev),
			       /*alignment*/CS461x_BUFFSIZE,
			       /*boundary*/CS461x_BUFFSIZE,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/NULL, /*filterarg*/NULL,
			       /*maxsize*/CS461x_BUFFSIZE, /*nsegments*/1, /*maxsegz*/0x3ffff,
			       /*flags*/0, /*lockfunc*/busdma_lock_mutex,
			       /*lockarg*/&Giant, &csa->parent_dmat) != 0)
		return (1);

	return (0);
}
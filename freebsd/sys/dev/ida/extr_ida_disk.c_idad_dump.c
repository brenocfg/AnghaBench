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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct idad_softc {TYPE_1__* controller; int /*<<< orphan*/  drive; } ;
struct disk {struct idad_softc* d_drv1; } ;
typedef  int off_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WRITE ; 
 int DEV_BSIZE ; 
 int /*<<< orphan*/  DMA_DATA_OUT ; 
 int ENXIO ; 
 int /*<<< orphan*/  IDA_INTERRUPTS ; 
 int ida_command (TYPE_1__*,int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
idad_dump(void *arg, void *virtual, vm_offset_t physical, off_t offset, size_t length)
{

	struct idad_softc *drv;
	int error = 0;
	struct disk *dp;

	dp = arg;
	drv = dp->d_drv1;
	if (drv == NULL)
		return (ENXIO);

	drv->controller->flags &= ~IDA_INTERRUPTS;

	if (length > 0) {
		error = ida_command(drv->controller, CMD_WRITE, virtual,
		    length, drv->drive, offset / DEV_BSIZE, DMA_DATA_OUT);
	}
	drv->controller->flags |= IDA_INTERRUPTS;
	return (error);
}
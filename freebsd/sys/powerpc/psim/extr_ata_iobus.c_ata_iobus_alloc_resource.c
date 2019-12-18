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
typedef  int u_int ;
struct resource {int dummy; } ;
typedef  int rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  ATA_BMADDR_RID 130 
#define  ATA_CTLADDR_RID 129 
 int ATA_CTLIOSIZE ; 
#define  ATA_IOADDR_RID 128 
 int ATA_IOSIZE ; 
 int ATA_IRQ_RID ; 
 struct resource* BUS_ALLOC_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int,int,int,int) ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_IRQ ; 
 int SYS_RES_MEMORY ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int* iobus_get_regs (int /*<<< orphan*/ ) ; 

struct resource *
ata_iobus_alloc_resource(device_t dev, device_t child, int type, int *rid,
			 rman_res_t start, rman_res_t end, rman_res_t count,
			 u_int flags)
{
	struct resource *res = NULL;
	int myrid;
	u_int *ofw_regs;

	ofw_regs = iobus_get_regs(dev);

	/*
	 * The reg array for the PSIM ata device has 6 start/size entries:
	 *  0 - unused
	 *  1/2/3 - unused
	 *  4/5/6 - primary command
	 *  7/8/9 - secondary command
	 *  10/11/12 - primary control
	 *  13/14/15 - secondary control
	 *  16/17/18 - primary/secondary dma registers, unimplemented
	 *
	 *  The resource values are calculated from these registers
	 */
	if (type == SYS_RES_IOPORT) {
		switch (*rid) {
		case ATA_IOADDR_RID:
			myrid = 0;
			start = ofw_regs[4];
			end = start + ATA_IOSIZE - 1;
			count = ATA_IOSIZE;
			res = BUS_ALLOC_RESOURCE(device_get_parent(dev), child,
						 SYS_RES_MEMORY, &myrid,
						 start, end, count, flags);
			break;

		case ATA_CTLADDR_RID:
			myrid = 0;
			start = ofw_regs[10];
			end = start + ATA_CTLIOSIZE - 1;
			count = ATA_CTLIOSIZE;
			res = BUS_ALLOC_RESOURCE(device_get_parent(dev), child,
						 SYS_RES_MEMORY, &myrid,
						 start, end, count, flags);
			break;

		case ATA_BMADDR_RID:
			/* DMA not properly supported by psim */
			break;
		}
		return (res);

	} else if (type == SYS_RES_IRQ && *rid == ATA_IRQ_RID) {
		/*
		 * Pass this on to the parent
		 */
		return (BUS_ALLOC_RESOURCE(device_get_parent(dev), dev,
					   SYS_RES_IRQ, rid, 0, ~0, 1, flags));

	} else {
		return (NULL);
	}
}
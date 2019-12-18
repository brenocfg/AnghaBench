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
struct superio_devinfo {uintptr_t ldn; uintptr_t type; uintptr_t iobase; uintptr_t iobase2; uintptr_t irq; uintptr_t dma; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  SUPERIO_IVAR_DMA 133 
#define  SUPERIO_IVAR_IOBASE 132 
#define  SUPERIO_IVAR_IOBASE2 131 
#define  SUPERIO_IVAR_IRQ 130 
#define  SUPERIO_IVAR_LDN 129 
#define  SUPERIO_IVAR_TYPE 128 
 struct superio_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
superio_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
	struct superio_devinfo *dinfo;

	dinfo = device_get_ivars(child);
	switch (which) {
	case SUPERIO_IVAR_LDN:
		*result = dinfo->ldn;
		break;
	case SUPERIO_IVAR_TYPE:
		*result = dinfo->type;
		break;
	case SUPERIO_IVAR_IOBASE:
		*result = dinfo->iobase;
		break;
	case SUPERIO_IVAR_IOBASE2:
		*result = dinfo->iobase2;
		break;
	case SUPERIO_IVAR_IRQ:
		*result = dinfo->irq;
		break;
	case SUPERIO_IVAR_DMA:
		*result = dinfo->dma;
		break;
	default:
		return (ENOENT);
	}
	return (0);
}
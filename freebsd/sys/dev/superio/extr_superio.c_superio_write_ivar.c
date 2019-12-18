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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
#define  SUPERIO_IVAR_DMA 133 
#define  SUPERIO_IVAR_IOBASE 132 
#define  SUPERIO_IVAR_IOBASE2 131 
#define  SUPERIO_IVAR_IRQ 130 
#define  SUPERIO_IVAR_LDN 129 
#define  SUPERIO_IVAR_TYPE 128 

__attribute__((used)) static int
superio_write_ivar(device_t dev, device_t child, int which, uintptr_t value)
{

	switch (which) {
	case SUPERIO_IVAR_LDN:
	case SUPERIO_IVAR_TYPE:
	case SUPERIO_IVAR_IOBASE:
	case SUPERIO_IVAR_IOBASE2:
	case SUPERIO_IVAR_IRQ:
	case SUPERIO_IVAR_DMA:
		return (EINVAL);
	default:
		return (ENOENT);
	}
}
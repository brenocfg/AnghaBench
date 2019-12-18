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
struct isa_device {uintptr_t id_vendorid; uintptr_t id_serial; uintptr_t id_logicalid; uintptr_t id_compatid; uintptr_t id_config_attr; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct isa_device* DEVTOISA (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOENT ; 
#define  ISA_IVAR_COMPATID 144 
#define  ISA_IVAR_CONFIGATTR 143 
#define  ISA_IVAR_DRQ_0 142 
#define  ISA_IVAR_DRQ_1 141 
#define  ISA_IVAR_IRQ_0 140 
#define  ISA_IVAR_IRQ_1 139 
#define  ISA_IVAR_LOGICALID 138 
#define  ISA_IVAR_MADDR_0 137 
#define  ISA_IVAR_MADDR_1 136 
#define  ISA_IVAR_MEMSIZE_0 135 
#define  ISA_IVAR_MEMSIZE_1 134 
#define  ISA_IVAR_PORTSIZE_0 133 
#define  ISA_IVAR_PORTSIZE_1 132 
#define  ISA_IVAR_PORT_0 131 
#define  ISA_IVAR_PORT_1 130 
#define  ISA_IVAR_SERIAL 129 
#define  ISA_IVAR_VENDORID 128 

__attribute__((used)) static int
isa_write_ivar(device_t bus, device_t dev, int index, uintptr_t value)
{
	struct isa_device* idev = DEVTOISA(dev);

	switch (index) {
	case ISA_IVAR_PORT_0:
	case ISA_IVAR_PORT_1:
	case ISA_IVAR_PORTSIZE_0:
	case ISA_IVAR_PORTSIZE_1:
	case ISA_IVAR_MADDR_0:
	case ISA_IVAR_MADDR_1:
	case ISA_IVAR_MEMSIZE_0:
	case ISA_IVAR_MEMSIZE_1:
	case ISA_IVAR_IRQ_0:
	case ISA_IVAR_IRQ_1:
	case ISA_IVAR_DRQ_0:
	case ISA_IVAR_DRQ_1:
		return (EINVAL);

	case ISA_IVAR_VENDORID:
		idev->id_vendorid = value;
		break;

	case ISA_IVAR_SERIAL:
		idev->id_serial = value;
		break;

	case ISA_IVAR_LOGICALID:
		idev->id_logicalid = value;
		break;

	case ISA_IVAR_COMPATID:
		idev->id_compatid = value;
		break;

	case ISA_IVAR_CONFIGATTR:
		idev->id_config_attr = value;
		break;

	default:
		return (ENOENT);
	}

	return (0);
}
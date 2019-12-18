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
struct resource_list_entry {uintptr_t start; uintptr_t count; } ;
struct resource_list {int dummy; } ;
struct isa_device {uintptr_t id_vendorid; uintptr_t id_serial; uintptr_t id_logicalid; uintptr_t id_compatid; uintptr_t id_config_attr; uintptr_t id_pnp_csn; uintptr_t id_pnp_ldn; uintptr_t id_pnpbios_handle; struct resource_list id_resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct isa_device* DEVTOISA (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
#define  ISA_IVAR_COMPATID 147 
#define  ISA_IVAR_CONFIGATTR 146 
#define  ISA_IVAR_DRQ_0 145 
#define  ISA_IVAR_DRQ_1 144 
#define  ISA_IVAR_IRQ_0 143 
#define  ISA_IVAR_IRQ_1 142 
#define  ISA_IVAR_LOGICALID 141 
#define  ISA_IVAR_MADDR_0 140 
#define  ISA_IVAR_MADDR_1 139 
#define  ISA_IVAR_MEMSIZE_0 138 
#define  ISA_IVAR_MEMSIZE_1 137 
#define  ISA_IVAR_PNPBIOS_HANDLE 136 
#define  ISA_IVAR_PNP_CSN 135 
#define  ISA_IVAR_PNP_LDN 134 
#define  ISA_IVAR_PORTSIZE_0 133 
#define  ISA_IVAR_PORTSIZE_1 132 
#define  ISA_IVAR_PORT_0 131 
#define  ISA_IVAR_PORT_1 130 
#define  ISA_IVAR_SERIAL 129 
#define  ISA_IVAR_VENDORID 128 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
isa_read_ivar(device_t bus, device_t dev, int index, uintptr_t * result)
{
	struct isa_device* idev = DEVTOISA(dev);
	struct resource_list *rl = &idev->id_resources;
	struct resource_list_entry *rle;

	switch (index) {
	case ISA_IVAR_PORT_0:
		rle = resource_list_find(rl, SYS_RES_IOPORT, 0);
		if (rle)
			*result = rle->start;
		else
			*result = -1;
		break;

	case ISA_IVAR_PORT_1:
		rle = resource_list_find(rl, SYS_RES_IOPORT, 1);
		if (rle)
			*result = rle->start;
		else
			*result = -1;
		break;

	case ISA_IVAR_PORTSIZE_0:
		rle = resource_list_find(rl, SYS_RES_IOPORT, 0);
		if (rle)
			*result = rle->count;
		else
			*result = 0;
		break;

	case ISA_IVAR_PORTSIZE_1:
		rle = resource_list_find(rl, SYS_RES_IOPORT, 1);
		if (rle)
			*result = rle->count;
		else
			*result = 0;
		break;

	case ISA_IVAR_MADDR_0:
		rle = resource_list_find(rl, SYS_RES_MEMORY, 0);
		if (rle)
			*result = rle->start;
		else
			*result = -1;
		break;

	case ISA_IVAR_MADDR_1:
		rle = resource_list_find(rl, SYS_RES_MEMORY, 1);
		if (rle)
			*result = rle->start;
		else
			*result = -1;
		break;

	case ISA_IVAR_MEMSIZE_0:
		rle = resource_list_find(rl, SYS_RES_MEMORY, 0);
		if (rle)
			*result = rle->count;
		else
			*result = 0;
		break;

	case ISA_IVAR_MEMSIZE_1:
		rle = resource_list_find(rl, SYS_RES_MEMORY, 1);
		if (rle)
			*result = rle->count;
		else
			*result = 0;
		break;

	case ISA_IVAR_IRQ_0:
		rle = resource_list_find(rl, SYS_RES_IRQ, 0);
		if (rle)
			*result = rle->start;
		else
			*result = -1;
		break;

	case ISA_IVAR_IRQ_1:
		rle = resource_list_find(rl, SYS_RES_IRQ, 1);
		if (rle)
			*result = rle->start;
		else
			*result = -1;
		break;

	case ISA_IVAR_DRQ_0:
		rle = resource_list_find(rl, SYS_RES_DRQ, 0);
		if (rle)
			*result = rle->start;
		else
			*result = -1;
		break;

	case ISA_IVAR_DRQ_1:
		rle = resource_list_find(rl, SYS_RES_DRQ, 1);
		if (rle)
			*result = rle->start;
		else
			*result = -1;
		break;

	case ISA_IVAR_VENDORID:
		*result = idev->id_vendorid;
		break;

	case ISA_IVAR_SERIAL:
		*result = idev->id_serial;
		break;

	case ISA_IVAR_LOGICALID:
		*result = idev->id_logicalid;
		break;

	case ISA_IVAR_COMPATID:
		*result = idev->id_compatid;
		break;

	case ISA_IVAR_CONFIGATTR:
		*result = idev->id_config_attr;
		break;

	case ISA_IVAR_PNP_CSN:
		*result = idev->id_pnp_csn;
		break;

	case ISA_IVAR_PNP_LDN:
		*result = idev->id_pnp_ldn;
		break;

	case ISA_IVAR_PNPBIOS_HANDLE:
		*result = idev->id_pnpbios_handle;
		break;

	default:
		return (ENOENT);
	}

	return (0);
}
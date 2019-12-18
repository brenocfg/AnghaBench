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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {struct lio_dispatch* dlist; } ;
struct octeon_device {TYPE_1__ dispatch; void* chip; } ;
struct lio_dispatch {int dummy; } ;
struct lio_cn23xx_pf {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  LIO_CN23XX_PF_VID 128 
 int LIO_DISPATCH_LIST_SIZE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct octeon_device *
lio_allocate_device_mem(device_t device)
{
	struct octeon_device	*oct;
	uint32_t	configsize = 0, pci_id = 0, size;
	uint8_t		*buf = NULL;

	pci_id = pci_get_device(device);
	switch (pci_id) {
	case LIO_CN23XX_PF_VID:
		configsize = sizeof(struct lio_cn23xx_pf);
		break;
	default:
		device_printf(device, "Error: Unknown PCI Device: 0x%x\n",
			      pci_id);
		return (NULL);
	}

	if (configsize & 0x7)
		configsize += (8 - (configsize & 0x7));

	size = configsize +
		(sizeof(struct lio_dispatch) * LIO_DISPATCH_LIST_SIZE);

	buf = malloc(size, M_DEVBUF, M_NOWAIT | M_ZERO);
	if (buf == NULL)
		return (NULL);

	oct = (struct octeon_device *)device_get_softc(device);
	oct->chip = (void *)(buf);
	oct->dispatch.dlist = (struct lio_dispatch *)(buf + configsize);

	return (oct);
}
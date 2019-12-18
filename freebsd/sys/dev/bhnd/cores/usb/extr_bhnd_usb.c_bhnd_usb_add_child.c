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
struct bhnd_usb_softc {scalar_t__ sc_maddr; } ;
struct bhnd_usb_devinfo {int sdi_irq_mapped; int sdi_msize; int /*<<< orphan*/  sdi_rl; scalar_t__ sdi_irq; scalar_t__ sdi_maddr; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_ERROR_DEV (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  BHND_INFO_DEV (int /*<<< orphan*/ *,char*,char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bhnd_map_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  bhnd_unmap_intr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * device_add_child_ordered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 struct bhnd_usb_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct bhnd_usb_devinfo*) ; 
 int /*<<< orphan*/  free (struct bhnd_usb_devinfo*,int /*<<< orphan*/ ) ; 
 struct bhnd_usb_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static device_t
bhnd_usb_add_child(device_t dev, u_int order, const char *name, int unit)
{
	struct bhnd_usb_softc		*sc;
	struct bhnd_usb_devinfo 	*sdi;
	device_t 			 child;
	int				 error;

	sc = device_get_softc(dev);

	sdi = malloc(sizeof(struct bhnd_usb_devinfo), M_DEVBUF, M_NOWAIT|M_ZERO);
	if (sdi == NULL)
		return (NULL);

	resource_list_init(&sdi->sdi_rl);
	sdi->sdi_irq_mapped = false;

	if (strncmp(name, "ohci", 4) == 0) 
	{
		sdi->sdi_maddr = sc->sc_maddr + 0x000;
		sdi->sdi_msize = 0x200;
	}
	else if (strncmp(name, "ehci", 4) == 0) 
	{
		sdi->sdi_maddr = sc->sc_maddr + 0x000;
		sdi->sdi_msize = 0x1000;
	}
	else
	{
		panic("Unknown subdevice");
	}

	/* Map the child's IRQ */
	if ((error = bhnd_map_intr(dev, 0, &sdi->sdi_irq))) {
		BHND_ERROR_DEV(dev, "could not map %s interrupt: %d", name,
		    error);
		goto failed;
	}
	sdi->sdi_irq_mapped = true;

	BHND_INFO_DEV(dev, "%s: irq=%ju maddr=0x%jx", name, sdi->sdi_irq,
	    sdi->sdi_maddr);

	/*
	 * Add memory window and irq to child's resource list.
	 */
	resource_list_add(&sdi->sdi_rl, SYS_RES_MEMORY, 0, sdi->sdi_maddr,
	    sdi->sdi_maddr + sdi->sdi_msize - 1, sdi->sdi_msize);

	resource_list_add(&sdi->sdi_rl, SYS_RES_IRQ, 0, sdi->sdi_irq,
	    sdi->sdi_irq, 1);

	child = device_add_child_ordered(dev, order, name, unit);
	if (child == NULL) {
		BHND_ERROR_DEV(dev, "could not add %s", name);
		goto failed;
	}

	device_set_ivars(child, sdi);
	return (child);

failed:
	if (sdi->sdi_irq_mapped)
		bhnd_unmap_intr(dev, sdi->sdi_irq);

	resource_list_free(&sdi->sdi_rl);

	free(sdi, M_DEVBUF);
	return (NULL);
}
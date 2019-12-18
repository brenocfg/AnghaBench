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
struct bhnd_erom_io {int dummy; } ;
struct bhnd_chipid {int dummy; } ;
struct bcma_erom {int dummy; } ;
struct bcma_devinfo {int dummy; } ;
struct bcma_corecfg {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  bhnd_erom_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_EROM_RID ; 
 int /*<<< orphan*/  BHND_BUS_CHILD_ADDED (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct bhnd_chipid* BHND_BUS_GET_CHIPID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENXIO ; 
 int bcma_erom_next_corecfg (struct bcma_erom*,struct bcma_corecfg**) ; 
 int /*<<< orphan*/  bcma_erom_parser ; 
 int /*<<< orphan*/  bcma_free_corecfg (struct bcma_corecfg*) ; 
 int bcma_init_dinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bcma_devinfo*,struct bcma_corecfg*) ; 
 int /*<<< orphan*/ * bhnd_erom_alloc (int /*<<< orphan*/ *,struct bhnd_chipid const*,struct bhnd_erom_io*) ; 
 int /*<<< orphan*/  bhnd_erom_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_erom_io_fini (struct bhnd_erom_io*) ; 
 struct bhnd_erom_io* bhnd_erom_iores_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bhnd_is_hw_disabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_disable (int /*<<< orphan*/ *) ; 
 struct bcma_devinfo* device_get_ivars (int /*<<< orphan*/ *) ; 

int
bcma_add_children(device_t bus)
{
	bhnd_erom_t			*erom;
	struct bcma_erom		*bcma_erom;
	struct bhnd_erom_io		*eio;
	const struct bhnd_chipid	*cid;
	struct bcma_corecfg		*corecfg;
	struct bcma_devinfo		*dinfo;
	device_t			 child;
	int				 error;

	cid = BHND_BUS_GET_CHIPID(bus, bus);
	corecfg = NULL;

	/* Allocate our EROM parser */
	eio = bhnd_erom_iores_new(bus, BCMA_EROM_RID);
	erom = bhnd_erom_alloc(&bcma_erom_parser, cid, eio);
	if (erom == NULL) {
		bhnd_erom_io_fini(eio);
		return (ENODEV);
	}

	/* Add all cores. */
	bcma_erom = (struct bcma_erom *)erom;
	while ((error = bcma_erom_next_corecfg(bcma_erom, &corecfg)) == 0) {
		/* Add the child device */
		child = BUS_ADD_CHILD(bus, 0, NULL, -1);
		if (child == NULL) {
			error = ENXIO;
			goto cleanup;
		}

		/* Initialize device ivars */
		dinfo = device_get_ivars(child);
		if ((error = bcma_init_dinfo(bus, child, dinfo, corecfg)))
			goto cleanup;

		/* The dinfo instance now owns the corecfg value */
		corecfg = NULL;

		/* If pins are floating or the hardware is otherwise
		 * unpopulated, the device shouldn't be used. */
		if (bhnd_is_hw_disabled(child))
			device_disable(child);

		/* Issue bus callback for fully initialized child. */
		BHND_BUS_CHILD_ADDED(bus, child);
	}

	/* EOF while parsing cores is expected */
	if (error == ENOENT)
		error = 0;
	
cleanup:
	bhnd_erom_free(erom);

	if (corecfg != NULL)
		bcma_free_corecfg(corecfg);

	if (error)
		device_delete_children(bus);

	return (error);
}
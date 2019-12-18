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
struct bhnd_chipid {scalar_t__ enum_addr; } ;
struct bcma_erom {struct bhnd_erom_io* eio; scalar_t__ offset; } ;
typedef  int /*<<< orphan*/  bhnd_erom_t ;
typedef  scalar_t__ bhnd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_EROM_TABLE_SIZE ; 
 scalar_t__ BCMA_EROM_TABLE_START ; 
 scalar_t__ BHND_ADDR_MAX ; 
 int ENXIO ; 
 int bhnd_erom_io_map (struct bhnd_erom_io*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bcma_erom_init(bhnd_erom_t *erom, const struct bhnd_chipid *cid,
    struct bhnd_erom_io *eio)
{
	struct bcma_erom	*sc;
	bhnd_addr_t		 table_addr;
	int			 error;

	sc = (struct bcma_erom *)erom;
	sc->eio = eio;
	sc->offset = 0;

	/* Determine erom table address */
	if (BHND_ADDR_MAX - BCMA_EROM_TABLE_START < cid->enum_addr)
		return (ENXIO); /* would overflow */

	table_addr = cid->enum_addr + BCMA_EROM_TABLE_START;

	/* Try to map the erom table */
	error = bhnd_erom_io_map(sc->eio, table_addr, BCMA_EROM_TABLE_SIZE);
	if (error)
		return (error);

	return (0);
}
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
struct bhnd_erom_iobus {scalar_t__ addr; scalar_t__ size; int mapped; scalar_t__ limit; scalar_t__ offset; } ;
struct bhnd_erom_io {int dummy; } ;
typedef  scalar_t__ bhnd_size_t ;
typedef  scalar_t__ bhnd_addr_t ;

/* Variables and functions */
 scalar_t__ BHND_ADDR_MAX ; 
 scalar_t__ BUS_SPACE_MAXSIZE ; 
 int EINVAL ; 
 int ENXIO ; 

__attribute__((used)) static int
bhnd_erom_iobus_map(struct bhnd_erom_io *eio, bhnd_addr_t addr,
    bhnd_size_t size)
{
	struct bhnd_erom_iobus *iobus = (struct bhnd_erom_iobus *)eio;

	/* Sanity check the addr/size */
	if (size == 0)
		return (EINVAL);

	/* addr+size must not overflow */
	if (BHND_ADDR_MAX - size < addr)
		return (EINVAL);

	/* addr/size must fit within our bus tag's mapping */
	if (addr < iobus->addr || size > iobus->size)
		return (ENXIO);

	if (iobus->size - (addr - iobus->addr) < size)
		return (ENXIO);

	/* The new addr offset and size must be representible as a bus_size_t */
	if ((addr - iobus->addr) > BUS_SPACE_MAXSIZE)
		return (ENXIO);

	if (size > BUS_SPACE_MAXSIZE)
		return (ENXIO);

	iobus->offset = addr - iobus->addr;
	iobus->limit = size;
	iobus->mapped = true;

	return (0);
}
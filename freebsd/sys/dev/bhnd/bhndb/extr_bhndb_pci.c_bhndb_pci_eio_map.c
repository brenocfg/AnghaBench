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
struct bhndb_pci_eio {int mapped; scalar_t__ size; scalar_t__ addr; } ;
struct bhnd_erom_io {int dummy; } ;
typedef  scalar_t__ bhnd_size_t ;
typedef  scalar_t__ bhnd_addr_t ;

/* Variables and functions */
 scalar_t__ BHND_ADDR_MAX ; 
 int EINVAL ; 

__attribute__((used)) static int
bhndb_pci_eio_map(struct bhnd_erom_io *eio, bhnd_addr_t addr,
    bhnd_size_t size)
{
	struct bhndb_pci_eio *pio = (struct bhndb_pci_eio *)eio;

	if (BHND_ADDR_MAX - addr < size)
		return (EINVAL); /* addr+size would overflow */

	pio->addr = addr;
	pio->size = size;
	pio->mapped = true;

	return (0);
}
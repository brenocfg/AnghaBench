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
struct bhndb_pci_eio {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; int /*<<< orphan*/  mapped; } ;
struct bhnd_erom_io {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_size_t ;
typedef  int /*<<< orphan*/  bhnd_addr_t ;

/* Variables and functions */
 int ENXIO ; 

__attribute__((used)) static int
bhndb_pci_eio_tell(struct bhnd_erom_io *eio, bhnd_addr_t *addr,
    bhnd_size_t *size)
{
	struct bhndb_pci_eio *pio = (struct bhndb_pci_eio *)eio;

	if (!pio->mapped)
		return (ENXIO);

	*addr = pio->addr;
	*size = pio->size;

	return (0);
}
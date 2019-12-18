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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int ;
struct bhndb_pci_eio {scalar_t__ size; int /*<<< orphan*/  addr; int /*<<< orphan*/  probe; int /*<<< orphan*/  mapped; } ;
struct bhnd_erom_io {int dummy; } ;
typedef  scalar_t__ bhnd_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  bhndb_pci_probe_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,...) ; 

__attribute__((used)) static uint32_t
bhndb_pci_eio_read(struct bhnd_erom_io *eio, bhnd_size_t offset, u_int width)
{
	struct bhndb_pci_eio *pio = (struct bhndb_pci_eio *)eio;

	/* Must have a valid mapping */
	if (!pio->mapped) 
		panic("no active mapping");

	/* The requested subrange must fall within the existing mapped range */
	if (offset > pio->size ||
	    width > pio->size ||
	    pio->size - offset < width)
	{
		panic("invalid offset %#jx", offset);
	}

	return (bhndb_pci_probe_read(pio->probe, pio->addr, offset, width));
}
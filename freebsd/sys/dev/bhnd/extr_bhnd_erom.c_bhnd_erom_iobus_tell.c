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
struct bhnd_erom_iobus {int /*<<< orphan*/  limit; scalar_t__ offset; scalar_t__ addr; int /*<<< orphan*/  mapped; } ;
struct bhnd_erom_io {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_size_t ;
typedef  scalar_t__ bhnd_addr_t ;

/* Variables and functions */
 int ENXIO ; 

__attribute__((used)) static int
bhnd_erom_iobus_tell(struct bhnd_erom_io *eio, bhnd_addr_t *addr,
    bhnd_size_t *size)
{
	struct bhnd_erom_iobus *iobus = (struct bhnd_erom_iobus *)eio;

	if (!iobus->mapped)
		return (ENXIO);

	*addr = iobus->addr + iobus->offset;
	*size = iobus->limit;

	return (0);
}
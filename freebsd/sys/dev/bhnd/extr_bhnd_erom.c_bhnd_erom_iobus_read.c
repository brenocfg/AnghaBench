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
struct bhnd_erom_iobus {scalar_t__ limit; scalar_t__ offset; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  mapped; } ;
struct bhnd_erom_io {int dummy; } ;
typedef  scalar_t__ bhnd_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_space_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*,...) ; 

__attribute__((used)) static uint32_t
bhnd_erom_iobus_read(struct bhnd_erom_io *eio, bhnd_size_t offset, u_int width)
{
	struct bhnd_erom_iobus *iobus = (struct bhnd_erom_iobus *)eio;

	if (!iobus->mapped) 
		panic("no active mapping");

	if (iobus->limit < width || iobus->limit - width < offset)
		panic("invalid offset %#jx", offset);

	switch (width) {
	case 1:
		return (bus_space_read_1(iobus->bst, iobus->bsh,
		    iobus->offset + offset));
	case 2:
		return (bus_space_read_2(iobus->bst, iobus->bsh,
		    iobus->offset + offset));
	case 4:
		return (bus_space_read_4(iobus->bst, iobus->bsh,
		    iobus->offset + offset));
	default:
		panic("invalid width %u", width);
	}
}
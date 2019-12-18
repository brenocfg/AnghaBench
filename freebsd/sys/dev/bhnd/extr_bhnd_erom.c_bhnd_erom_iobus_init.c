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
struct TYPE_2__ {int /*<<< orphan*/ * fini; int /*<<< orphan*/  read; int /*<<< orphan*/  tell; int /*<<< orphan*/  map; } ;
struct bhnd_erom_iobus {int mapped; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; TYPE_1__ eio; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  bhnd_size_t ;
typedef  int /*<<< orphan*/  bhnd_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  bhnd_erom_iobus_map ; 
 int /*<<< orphan*/  bhnd_erom_iobus_read ; 
 int /*<<< orphan*/  bhnd_erom_iobus_tell ; 

int
bhnd_erom_iobus_init(struct bhnd_erom_iobus *iobus, bhnd_addr_t addr,
    bhnd_size_t size, bus_space_tag_t bst, bus_space_handle_t bsh)
{
	iobus->eio.map = bhnd_erom_iobus_map;
	iobus->eio.tell = bhnd_erom_iobus_tell;
	iobus->eio.read = bhnd_erom_iobus_read;
	iobus->eio.fini = NULL;

	iobus->addr = addr;
	iobus->size = size;
	iobus->bst = bst;
	iobus->bsh = bsh;
	iobus->mapped = false;

	return (0);
}
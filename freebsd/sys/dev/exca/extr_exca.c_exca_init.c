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
struct exca_softc {int /*<<< orphan*/  putb; int /*<<< orphan*/  getb; scalar_t__ flags; int /*<<< orphan*/  offset; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; scalar_t__ ioalloc; scalar_t__ memalloc; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  exca_mem_getb ; 
 int /*<<< orphan*/  exca_mem_putb ; 

void
exca_init(struct exca_softc *sc, device_t dev, 
    bus_space_tag_t bst, bus_space_handle_t bsh, uint32_t offset)
{
	sc->dev = dev;
	sc->memalloc = 0;
	sc->ioalloc = 0;
	sc->bst = bst;
	sc->bsh = bsh;
	sc->offset = offset;
	sc->flags = 0;
	sc->getb = exca_mem_getb;
	sc->putb = exca_mem_putb;
}
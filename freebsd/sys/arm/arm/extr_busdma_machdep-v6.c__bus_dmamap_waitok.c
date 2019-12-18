#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct memdesc {int dummy; } ;
typedef  TYPE_1__* bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dmamap_callback_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
struct TYPE_3__ {void* callback_arg; int /*<<< orphan*/ * callback; int /*<<< orphan*/  dmat; struct memdesc mem; } ;

/* Variables and functions */

void
_bus_dmamap_waitok(bus_dma_tag_t dmat, bus_dmamap_t map, struct memdesc *mem,
    bus_dmamap_callback_t *callback, void *callback_arg)
{

	map->mem = *mem;
	map->dmat = dmat;
	map->callback = callback;
	map->callback_arg = callback_arg;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bus_dmamap_t ;
typedef  TYPE_2__* bus_dma_tag_t ;
struct TYPE_4__ {int /*<<< orphan*/  map_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  bpages; scalar_t__ sync_count; int /*<<< orphan*/ * allocbuffer; int /*<<< orphan*/ * slist; scalar_t__ flags; TYPE_2__* dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dmamap_ctor(void *mem, int size, void *arg, int flags)
{
	bus_dmamap_t map;
	bus_dma_tag_t dmat;

	map = (bus_dmamap_t)mem;
	dmat = (bus_dma_tag_t)arg;

	dmat->map_count++;

	map->dmat = dmat;
	map->flags = 0;
	map->slist = NULL;
	map->allocbuffer = NULL;
	map->sync_count = 0;
	STAILQ_INIT(&map->bpages);

	return (0);
}
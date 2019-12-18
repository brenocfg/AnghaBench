#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct sync_list {int dummy; } ;
typedef  TYPE_2__* bus_dmamap_t ;
typedef  TYPE_3__* bus_dma_tag_t ;
struct TYPE_7__ {int nsegments; } ;
struct TYPE_9__ {TYPE_1__ common; } ;
struct TYPE_8__ {int /*<<< orphan*/  bpages; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bus_dmamap_t
alloc_dmamap(bus_dma_tag_t dmat, int flags)
{
	u_long mapsize;
	bus_dmamap_t map;

	mapsize = sizeof(*map);
	mapsize += sizeof(struct sync_list) * dmat->common.nsegments;
	map = malloc(mapsize, M_DEVBUF, flags | M_ZERO);
	if (map == NULL)
		return (NULL);

	/* Initialize the new map */
	STAILQ_INIT(&map->bpages);

	return (map);
}
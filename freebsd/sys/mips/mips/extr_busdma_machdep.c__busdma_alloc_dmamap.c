#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sync_list {int dummy; } ;
typedef  TYPE_1__* bus_dmamap_t ;
typedef  TYPE_2__* bus_dma_tag_t ;
struct TYPE_8__ {int nsegments; } ;
struct TYPE_7__ {struct sync_list* slist; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BUSDMA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  dmamap_zone ; 
 int /*<<< orphan*/  free (struct sync_list*,int /*<<< orphan*/ ) ; 
 struct sync_list* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* uma_zalloc_arg (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline bus_dmamap_t
_busdma_alloc_dmamap(bus_dma_tag_t dmat)
{
	struct sync_list *slist;
	bus_dmamap_t map;

	slist = malloc(sizeof(*slist) * dmat->nsegments, M_BUSDMA, M_NOWAIT);
	if (slist == NULL)
		return (NULL);
	map = uma_zalloc_arg(dmamap_zone, dmat, M_NOWAIT);
	if (map != NULL)
		map->slist = slist;
	else
		free(slist, M_BUSDMA);
	return (map);
}
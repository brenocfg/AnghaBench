#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bounce_zone {int /*<<< orphan*/  reserved_bpages; int /*<<< orphan*/  free_bpages; } ;
struct bounce_page {int dummy; } ;
typedef  TYPE_1__* bus_dmamap_t ;
typedef  TYPE_2__* bus_dma_tag_t ;
struct TYPE_7__ {struct bounce_zone* bounce_zone; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; scalar_t__ sync_count; scalar_t__ pagesneeded; scalar_t__ pagesreserved; int /*<<< orphan*/  bpages; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAMAP_MBUF ; 
 struct bounce_page* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_bounce_page (TYPE_2__*,struct bounce_page*) ; 
 int /*<<< orphan*/  links ; 

void
bus_dmamap_unload(bus_dma_tag_t dmat, bus_dmamap_t map)
{
	struct bounce_page *bpage;
	struct bounce_zone *bz;

	if ((bz = dmat->bounce_zone) != NULL) {
		while ((bpage = STAILQ_FIRST(&map->bpages)) != NULL) {
			STAILQ_REMOVE_HEAD(&map->bpages, links);
			free_bounce_page(dmat, bpage);
		}

		bz = dmat->bounce_zone;
		bz->free_bpages += map->pagesreserved;
		bz->reserved_bpages -= map->pagesreserved;
		map->pagesreserved = 0;
		map->pagesneeded = 0;
	}
	map->sync_count = 0;
	map->flags &= ~DMAMAP_MBUF;
}
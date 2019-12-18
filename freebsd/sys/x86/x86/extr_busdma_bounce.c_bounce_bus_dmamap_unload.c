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
struct bounce_page {int dummy; } ;
typedef  TYPE_1__* bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
struct TYPE_3__ {int /*<<< orphan*/  bpages; } ;

/* Variables and functions */
 struct bounce_page* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_bounce_page (int /*<<< orphan*/ ,struct bounce_page*) ; 
 int /*<<< orphan*/  links ; 

__attribute__((used)) static void
bounce_bus_dmamap_unload(bus_dma_tag_t dmat, bus_dmamap_t map)
{
	struct bounce_page *bpage;

	if (map == NULL)
		return;

	while ((bpage = STAILQ_FIRST(&map->bpages)) != NULL) {
		STAILQ_REMOVE_HEAD(&map->bpages, links);
		free_bounce_page(dmat, bpage);
	}
}
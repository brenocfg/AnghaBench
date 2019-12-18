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
struct bus_dmamap_dmar {int locked; int cansleep; struct bus_dma_tag_dmar* tag; int /*<<< orphan*/  map_entries; } ;
struct TYPE_2__ {int nsegments; int /*<<< orphan*/  domain; } ;
struct bus_dma_tag_dmar {int /*<<< orphan*/  map_count; int /*<<< orphan*/ * segments; TYPE_1__ common; } ;
typedef  int /*<<< orphan*/ * bus_dmamap_t ;
typedef  scalar_t__ bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAINSET_PREF (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_DMAR_DMAMAP ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_domain (struct bus_dmamap_dmar*,int /*<<< orphan*/ ) ; 
 void* malloc_domainset (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dmar_bus_dmamap_create(bus_dma_tag_t dmat, int flags, bus_dmamap_t *mapp)
{
	struct bus_dma_tag_dmar *tag;
	struct bus_dmamap_dmar *map;

	tag = (struct bus_dma_tag_dmar *)dmat;
	map = malloc_domainset(sizeof(*map), M_DMAR_DMAMAP,
	    DOMAINSET_PREF(tag->common.domain), M_NOWAIT | M_ZERO);
	if (map == NULL) {
		*mapp = NULL;
		return (ENOMEM);
	}
	if (tag->segments == NULL) {
		tag->segments = malloc_domainset(sizeof(bus_dma_segment_t) *
		    tag->common.nsegments, M_DMAR_DMAMAP,
		    DOMAINSET_PREF(tag->common.domain), M_NOWAIT);
		if (tag->segments == NULL) {
			free_domain(map, M_DMAR_DMAMAP);
			*mapp = NULL;
			return (ENOMEM);
		}
	}
	TAILQ_INIT(&map->map_entries);
	map->tag = tag;
	map->locked = true;
	map->cansleep = false;
	tag->map_count++;
	*mapp = (bus_dmamap_t)map;

	return (0);
}
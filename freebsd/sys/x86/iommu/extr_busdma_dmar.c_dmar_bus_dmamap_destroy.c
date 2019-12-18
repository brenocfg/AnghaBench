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
struct dmar_domain {int dummy; } ;
struct bus_dmamap_dmar {int /*<<< orphan*/  map_entries; } ;
struct bus_dma_tag_dmar {int /*<<< orphan*/  map_count; TYPE_1__* ctx; } ;
typedef  scalar_t__ bus_dmamap_t ;
typedef  scalar_t__ bus_dma_tag_t ;
struct TYPE_2__ {struct dmar_domain* domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_LOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_DOMAIN_UNLOCK (struct dmar_domain*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  M_DMAR_DMAMAP ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_domain (struct bus_dmamap_dmar*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dmar_bus_dmamap_destroy(bus_dma_tag_t dmat, bus_dmamap_t map1)
{
	struct bus_dma_tag_dmar *tag;
	struct bus_dmamap_dmar *map;
	struct dmar_domain *domain;

	tag = (struct bus_dma_tag_dmar *)dmat;
	map = (struct bus_dmamap_dmar *)map1;
	if (map != NULL) {
		domain = tag->ctx->domain;
		DMAR_DOMAIN_LOCK(domain);
		if (!TAILQ_EMPTY(&map->map_entries)) {
			DMAR_DOMAIN_UNLOCK(domain);
			return (EBUSY);
		}
		DMAR_DOMAIN_UNLOCK(domain);
		free_domain(map, M_DMAR_DMAMAP);
	}
	tag->map_count--;
	return (0);
}
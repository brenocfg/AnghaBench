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
struct dmar_map_entries_tailq {int dummy; } ;
struct dmar_domain {int /*<<< orphan*/  unload_task; TYPE_1__* dmar; struct dmar_map_entries_tailq unload_entries; } ;
struct dmar_ctx {int /*<<< orphan*/  unloads; struct dmar_domain* domain; } ;
struct bus_dmamap_dmar {int /*<<< orphan*/  map_entries; } ;
struct bus_dma_tag_dmar {struct dmar_ctx* ctx; } ;
typedef  scalar_t__ bus_dmamap_t ;
typedef  scalar_t__ bus_dma_tag_t ;
struct TYPE_2__ {int /*<<< orphan*/  delayed_taskqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_LOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_DOMAIN_UNLOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAILQ_CONCAT (struct dmar_map_entries_tailq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (struct dmar_map_entries_tailq*) ; 
 int /*<<< orphan*/  TAILQ_INIT (struct dmar_map_entries_tailq*) ; 
 int /*<<< orphan*/  THREAD_NO_SLEEPING () ; 
 int /*<<< orphan*/  THREAD_SLEEPING_OK () ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmamap_link ; 
 int /*<<< orphan*/  dmar_domain_unload (struct dmar_domain*,struct dmar_map_entries_tailq*,int) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dmar_bus_dmamap_unload(bus_dma_tag_t dmat, bus_dmamap_t map1)
{
	struct bus_dma_tag_dmar *tag;
	struct bus_dmamap_dmar *map;
	struct dmar_ctx *ctx;
	struct dmar_domain *domain;
#if defined(__amd64__)
	struct dmar_map_entries_tailq entries;
#endif

	tag = (struct bus_dma_tag_dmar *)dmat;
	map = (struct bus_dmamap_dmar *)map1;
	ctx = tag->ctx;
	domain = ctx->domain;
	atomic_add_long(&ctx->unloads, 1);

#if defined(__i386__)
	DMAR_DOMAIN_LOCK(domain);
	TAILQ_CONCAT(&domain->unload_entries, &map->map_entries, dmamap_link);
	DMAR_DOMAIN_UNLOCK(domain);
	taskqueue_enqueue(domain->dmar->delayed_taskqueue,
	    &domain->unload_task);
#else /* defined(__amd64__) */
	TAILQ_INIT(&entries);
	DMAR_DOMAIN_LOCK(domain);
	TAILQ_CONCAT(&entries, &map->map_entries, dmamap_link);
	DMAR_DOMAIN_UNLOCK(domain);
	THREAD_NO_SLEEPING();
	dmar_domain_unload(domain, &entries, false);
	THREAD_SLEEPING_OK();
	KASSERT(TAILQ_EMPTY(&entries), ("lazy dmar_ctx_unload %p", ctx));
#endif
}
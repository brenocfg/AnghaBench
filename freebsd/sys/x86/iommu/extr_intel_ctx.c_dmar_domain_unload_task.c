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
struct dmar_map_entries_tailq {int dummy; } ;
struct dmar_domain {int /*<<< orphan*/  unload_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_DOMAIN_LOCK (struct dmar_domain*) ; 
 int /*<<< orphan*/  DMAR_DOMAIN_UNLOCK (struct dmar_domain*) ; 
 scalar_t__ TAILQ_EMPTY (struct dmar_map_entries_tailq*) ; 
 int /*<<< orphan*/  TAILQ_INIT (struct dmar_map_entries_tailq*) ; 
 int /*<<< orphan*/  TAILQ_SWAP (int /*<<< orphan*/ *,struct dmar_map_entries_tailq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmamap_link ; 
 int /*<<< orphan*/  dmar_domain_unload (struct dmar_domain*,struct dmar_map_entries_tailq*,int) ; 
 int /*<<< orphan*/  dmar_map_entry ; 

__attribute__((used)) static void
dmar_domain_unload_task(void *arg, int pending)
{
	struct dmar_domain *domain;
	struct dmar_map_entries_tailq entries;

	domain = arg;
	TAILQ_INIT(&entries);

	for (;;) {
		DMAR_DOMAIN_LOCK(domain);
		TAILQ_SWAP(&domain->unload_entries, &entries, dmar_map_entry,
		    dmamap_link);
		DMAR_DOMAIN_UNLOCK(domain);
		if (TAILQ_EMPTY(&entries))
			break;
		dmar_domain_unload(domain, &entries, true);
	}
}
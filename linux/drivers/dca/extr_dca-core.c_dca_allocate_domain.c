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
struct pci_bus {int dummy; } ;
struct dca_domain {struct pci_bus* pci_rc; int /*<<< orphan*/  dca_providers; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct dca_domain* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dca_domain *dca_allocate_domain(struct pci_bus *rc)
{
	struct dca_domain *domain;

	domain = kzalloc(sizeof(*domain), GFP_NOWAIT);
	if (!domain)
		return NULL;

	INIT_LIST_HEAD(&domain->dca_providers);
	domain->pci_rc = rc;

	return domain;
}
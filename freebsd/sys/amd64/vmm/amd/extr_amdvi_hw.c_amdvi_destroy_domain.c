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
struct amdvi_domain {int id; int /*<<< orphan*/  ptp_level; scalar_t__ ptp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (struct amdvi_domain*,char*) ; 
 int /*<<< orphan*/  M_AMDVI ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct amdvi_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdvi_do_inv_domain (int,int) ; 
 int /*<<< orphan*/  amdvi_domain ; 
 int /*<<< orphan*/  amdvi_free_ptp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dom_head ; 
 int /*<<< orphan*/  free (struct amdvi_domain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
amdvi_destroy_domain(void *arg)
{
	struct amdvi_domain *domain;

	domain = (struct amdvi_domain *)arg;
	KASSERT(domain, ("domain is NULL"));
#ifdef AMDVI_DEBUG_CMD
	printf("Destroying domain %d\n", domain->id);
#endif
	if (domain->ptp)
		amdvi_free_ptp(domain->ptp, domain->ptp_level);

	amdvi_do_inv_domain(domain->id, false);
	SLIST_REMOVE(&dom_head, domain, amdvi_domain, next);
	free(domain, M_AMDVI);
}
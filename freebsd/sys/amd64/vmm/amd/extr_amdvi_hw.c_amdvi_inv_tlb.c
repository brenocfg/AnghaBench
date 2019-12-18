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
struct amdvi_domain {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (struct amdvi_domain*,char*) ; 
 int /*<<< orphan*/  amdvi_do_inv_domain (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
amdvi_inv_tlb(void *arg)
{
	struct amdvi_domain *domain;

	domain = (struct amdvi_domain *)arg;
	KASSERT(domain, ("domain is NULL"));
	amdvi_do_inv_domain(domain->id, false);
}
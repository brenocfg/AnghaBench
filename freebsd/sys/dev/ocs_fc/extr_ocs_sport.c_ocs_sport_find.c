#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ocs_sport_t ;
struct TYPE_4__ {int /*<<< orphan*/  lookup_lock; int /*<<< orphan*/ * lookup; int /*<<< orphan*/  ocs; } ;
typedef  TYPE_1__ ocs_domain_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_assert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ocs_sport_t *
ocs_sport_find(ocs_domain_t *domain, uint32_t d_id)
{
	ocs_sport_t *sport;

	ocs_assert(domain, NULL);
	ocs_lock(&domain->lookup_lock);
		if (domain->lookup == NULL) {
			ocs_log_test(domain->ocs, "assertion failed: domain->lookup is not valid\n");
			ocs_unlock(&domain->lookup_lock);
			return NULL;
		}

		sport = spv_get(domain->lookup, d_id);
	ocs_unlock(&domain->lookup_lock);
	return sport;
}
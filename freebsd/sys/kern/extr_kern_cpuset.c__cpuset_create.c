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
struct domainset {int dummy; } ;
struct cpuset {scalar_t__ cs_id; int /*<<< orphan*/  cs_children; int /*<<< orphan*/  cs_parent; int /*<<< orphan*/  cs_mask; struct domainset* cs_domain; scalar_t__ cs_flags; int /*<<< orphan*/  cs_ref; } ;
typedef  scalar_t__ cpusetid_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 scalar_t__ CPUSET_INVALID ; 
 int /*<<< orphan*/  CPU_AND (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_COPY (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_OVERLAP (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int EDEADLK ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct cpuset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuset_ids ; 
 int /*<<< orphan*/  cpuset_lock ; 
 int /*<<< orphan*/  cpuset_ref (struct cpuset*) ; 
 int /*<<< orphan*/  cs_link ; 
 int /*<<< orphan*/  cs_siblings ; 
 int /*<<< orphan*/  domainset_valid (struct domainset*,struct domainset*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
_cpuset_create(struct cpuset *set, struct cpuset *parent,
    const cpuset_t *mask, struct domainset *domain, cpusetid_t id)
{

	if (domain == NULL)
		domain = parent->cs_domain;
	if (mask == NULL)
		mask = &parent->cs_mask;
	if (!CPU_OVERLAP(&parent->cs_mask, mask))
		return (EDEADLK);
	/* The domain must be prepared ahead of time. */
	if (!domainset_valid(parent->cs_domain, domain))
		return (EDEADLK);
	CPU_COPY(mask, &set->cs_mask);
	LIST_INIT(&set->cs_children);
	refcount_init(&set->cs_ref, 1);
	set->cs_flags = 0;
	mtx_lock_spin(&cpuset_lock);
	set->cs_domain = domain;
	CPU_AND(&set->cs_mask, &parent->cs_mask);
	set->cs_id = id;
	set->cs_parent = cpuset_ref(parent);
	LIST_INSERT_HEAD(&parent->cs_children, set, cs_siblings);
	if (set->cs_id != CPUSET_INVALID)
		LIST_INSERT_HEAD(&cpuset_ids, set, cs_link);
	mtx_unlock_spin(&cpuset_lock);

	return (0);
}
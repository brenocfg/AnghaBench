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
typedef  int /*<<< orphan*/  vm_page_t ;
struct vm_pgcache {int /*<<< orphan*/  pool; int /*<<< orphan*/  domain; } ;
struct vm_domain {int vmd_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_ALLOC_NORMAL ; 
 struct vm_domain* VM_DOMAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_domain_allocate (struct vm_domain*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_domain_free_lock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_free_unlock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_freecnt_inc (struct vm_domain*,int) ; 
 int vm_phys_alloc_npages (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vm_page_zone_import(void *arg, void **store, int cnt, int domain, int flags)
{
	struct vm_domain *vmd;
	struct vm_pgcache *pgcache;
	int i;

	pgcache = arg;
	vmd = VM_DOMAIN(pgcache->domain);
	/* Only import if we can bring in a full bucket. */
	if (cnt == 1 || !vm_domain_allocate(vmd, VM_ALLOC_NORMAL, cnt))
		return (0);
	domain = vmd->vmd_domain;
	vm_domain_free_lock(vmd);
	i = vm_phys_alloc_npages(domain, pgcache->pool, cnt,
	    (vm_page_t *)store);
	vm_domain_free_unlock(vmd);
	if (cnt != i)
		vm_domain_freecnt_inc(vmd, cnt - i);

	return (i);
}
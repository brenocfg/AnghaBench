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
typedef  scalar_t__ vm_page_t ;
struct vm_pgcache {int /*<<< orphan*/  domain; } ;
struct vm_domain {int dummy; } ;

/* Variables and functions */
 struct vm_domain* VM_DOMAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_domain_free_lock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_free_unlock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_freecnt_inc (struct vm_domain*,int) ; 
 int /*<<< orphan*/  vm_phys_free_pages (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_page_zone_release(void *arg, void **store, int cnt)
{
	struct vm_domain *vmd;
	struct vm_pgcache *pgcache;
	vm_page_t m;
	int i;

	pgcache = arg;
	vmd = VM_DOMAIN(pgcache->domain);
	vm_domain_free_lock(vmd);
	for (i = 0; i < cnt; i++) {
		m = (vm_page_t)store[i];
		vm_phys_free_pages(m, 0);
	}
	vm_domain_free_unlock(vmd);
	vm_domain_freecnt_inc(vmd, cnt);
}
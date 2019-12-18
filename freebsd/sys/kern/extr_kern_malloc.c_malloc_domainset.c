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
struct vm_domainset_iter {int dummy; } ;
struct malloc_type {int dummy; } ;
struct domainset {int dummy; } ;

/* Variables and functions */
 void* malloc_domain (size_t,struct malloc_type*,int,int) ; 
 scalar_t__ vm_domainset_iter_policy (struct vm_domainset_iter*,int*) ; 
 int /*<<< orphan*/  vm_domainset_iter_policy_init (struct vm_domainset_iter*,struct domainset*,int*,int*) ; 

void *
malloc_domainset(size_t size, struct malloc_type *mtp, struct domainset *ds,
    int flags)
{
	struct vm_domainset_iter di;
	void *ret;
	int domain;

	vm_domainset_iter_policy_init(&di, ds, &domain, &flags);
	do {
		ret = malloc_domain(size, mtp, domain, flags);
		if (ret != NULL)
			break;
	} while (vm_domainset_iter_policy(&di, &domain) == 0);

	return (ret);
}
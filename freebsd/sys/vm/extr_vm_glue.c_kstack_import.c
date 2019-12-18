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
typedef  int /*<<< orphan*/  vm_object_t ;
struct domainset {int dummy; } ;

/* Variables and functions */
 struct domainset* DOMAINSET_PREF (int) ; 
 struct domainset* DOMAINSET_RR () ; 
 int UMA_ANYDOMAIN ; 
 int /*<<< orphan*/  kstack_pages ; 
 scalar_t__ vm_thread_stack_create (struct domainset*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kstack_import(void *arg, void **store, int cnt, int domain, int flags)
{
	struct domainset *ds;
	vm_object_t ksobj;
	int i;

	if (domain == UMA_ANYDOMAIN)
		ds = DOMAINSET_RR();
	else
		ds = DOMAINSET_PREF(domain);

	for (i = 0; i < cnt; i++) {
		store[i] = (void *)vm_thread_stack_create(ds, &ksobj,
		    kstack_pages);
		if (store[i] == NULL)
			break;
	}
	return (i);
}
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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  TYPE_1__* vm_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  rtree; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_page_alloc_domain_after (TYPE_1__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_radix_lookup_le (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

vm_page_t
vm_page_alloc_domain(vm_object_t object, vm_pindex_t pindex, int domain,
    int req)
{

	return (vm_page_alloc_domain_after(object, pindex, domain, req,
	    object != NULL ? vm_radix_lookup_le(&object->rtree, pindex) :
	    NULL));
}
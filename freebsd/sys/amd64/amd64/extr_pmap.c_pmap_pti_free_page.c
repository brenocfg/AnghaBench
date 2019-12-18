#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct TYPE_5__ {scalar_t__ ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  vm_page_free_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (TYPE_1__*) ; 

__attribute__((used)) static bool
pmap_pti_free_page(vm_page_t m)
{

	KASSERT(m->ref_count > 0, ("page %p not referenced", m));
	if (!vm_page_unwire_noq(m))
		return (false);
	vm_page_free_zero(m);
	return (true);
}
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
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int oflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  pmap_page_is_write_mapped (TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_page_test_mappings (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
pmap_is_modified(vm_page_t m)
{

	KASSERT((m->oflags & VPO_UNMANAGED) == 0,
	    ("pmap_is_modified: page %p is not managed", m));

	/*
	 * If the page is not busied then this check is racy.
	 */
	if (!pmap_page_is_write_mapped(m))
		return (FALSE);
	return (pmap_page_test_mappings(m, FALSE, TRUE));
}
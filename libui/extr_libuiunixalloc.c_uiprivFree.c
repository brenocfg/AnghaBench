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

/* Variables and functions */
 void* BASE (void*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  allocations ; 
 int /*<<< orphan*/  g_free (void*) ; 
 scalar_t__ g_ptr_array_remove (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  uiprivImplBug (char*,...) ; 

void uiprivFree(void *p)
{
	if (p == NULL)
		uiprivImplBug("attempt to uiprivFree(NULL)");
	p = BASE(p);
	g_free(p);
	if (g_ptr_array_remove(allocations, p) == FALSE)
		uiprivImplBug("%p not found in allocations array in uiprivFree()", p);
}
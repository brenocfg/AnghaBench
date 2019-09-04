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
 void* DATA (void*) ; 
 scalar_t__ EXTRA ; 
 size_t* SIZE (void*) ; 
 char const** TYPE (void*) ; 
 int /*<<< orphan*/  allocations ; 
 void* g_malloc0 (scalar_t__) ; 
 int /*<<< orphan*/  g_ptr_array_add (int /*<<< orphan*/ ,void*) ; 

void *uiprivAlloc(size_t size, const char *type)
{
	void *out;

	out = g_malloc0(EXTRA + size);
	*SIZE(out) = size;
	*TYPE(out) = type;
	g_ptr_array_add(allocations, out);
	return DATA(out);
}
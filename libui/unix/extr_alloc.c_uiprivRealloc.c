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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 void* BASE (void*) ; 
 void* DATA (void*) ; 
 scalar_t__ EXTRA ; 
 scalar_t__ FALSE ; 
 size_t* SIZE (void*) ; 
 int /*<<< orphan*/  allocations ; 
 int /*<<< orphan*/  g_ptr_array_add (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ g_ptr_array_remove (int /*<<< orphan*/ ,void*) ; 
 void* g_realloc (void*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 void* uiprivAlloc (size_t,char const*) ; 
 int /*<<< orphan*/  uiprivImplBug (char*,void*) ; 

void *uiprivRealloc(void *p, size_t new, const char *type)
{
	void *out;
	size_t *s;

	if (p == NULL)
		return uiprivAlloc(new, type);
	p = BASE(p);
	out = g_realloc(p, EXTRA + new);
	s = SIZE(out);
	if (new > *s)
		memset(((uint8_t *) DATA(out)) + *s, 0, new - *s);
	*s = new;
	if (g_ptr_array_remove(allocations, p) == FALSE)
		uiprivImplBug("%p not found in allocations array in uiprivRealloc()", p);
	g_ptr_array_add(allocations, out);
	return DATA(out);
}
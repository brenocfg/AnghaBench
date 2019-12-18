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
 int /*<<< orphan*/  KM_SLEEP ; 
 void* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (void*,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 void* realloc (void*,size_t) ; 

__attribute__((used)) static void *
cacl_realloc(void *ptr, size_t size, size_t new_size)
{
#if defined(_KERNEL)
	void *tmp;

	tmp = kmem_alloc(new_size, KM_SLEEP);
	(void) memcpy(tmp, ptr, (size < new_size) ? size : new_size);
	kmem_free(ptr, size);
	return (tmp);
#else
	return (realloc(ptr, new_size));
#endif
}
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
 int /*<<< orphan*/  die (char*,unsigned long) ; 
 int /*<<< orphan*/  error (char*,unsigned long) ; 
 void* malloc (int) ; 
 scalar_t__ memory_limit_check (size_t,int) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 

__attribute__((used)) static void *do_xmalloc(size_t size, int gentle)
{
	void *ret;

	if (memory_limit_check(size, gentle))
		return NULL;
	ret = malloc(size);
	if (!ret && !size)
		ret = malloc(1);
	if (!ret) {
		if (!gentle)
			die("Out of memory, malloc failed (tried to allocate %lu bytes)",
			    (unsigned long)size);
		else {
			error("Out of memory, malloc failed (tried to allocate %lu bytes)",
			      (unsigned long)size);
			return NULL;
		}
	}
#ifdef XMALLOC_POISON
	memset(ret, 0xA5, size);
#endif
	return ret;
}
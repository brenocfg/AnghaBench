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
 int /*<<< orphan*/  ENOMEM ; 
 size_t EV_SIZE_MAX ; 
 void* calloc (size_t,size_t) ; 
 int /*<<< orphan*/  errno ; 
 void* memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* mm_malloc_fn_ (size_t) ; 

void *
event_mm_calloc_(size_t count, size_t size)
{
	if (count == 0 || size == 0)
		return NULL;

	if (mm_malloc_fn_) {
		size_t sz = count * size;
		void *p = NULL;
		if (count > EV_SIZE_MAX / size)
			goto error;
		p = mm_malloc_fn_(sz);
		if (p)
			return memset(p, 0, sz);
	} else {
		void *p = calloc(count, size);
#ifdef _WIN32
		/* Windows calloc doesn't reliably set ENOMEM */
		if (p == NULL)
			goto error;
#endif
		return p;
	}

error:
	errno = ENOMEM;
	return NULL;
}
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
 void* mm_realloc_fn_ (void*,size_t) ; 
 void* realloc (void*,size_t) ; 

void *
event_mm_realloc_(void *ptr, size_t sz)
{
	if (mm_realloc_fn_)
		return mm_realloc_fn_(ptr, sz);
	else
		return realloc(ptr, sz);
}
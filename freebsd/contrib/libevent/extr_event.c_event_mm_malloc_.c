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
 void* malloc (size_t) ; 
 void* mm_malloc_fn_ (size_t) ; 

void *
event_mm_malloc_(size_t sz)
{
	if (sz == 0)
		return NULL;

	if (mm_malloc_fn_)
		return mm_malloc_fn_(sz);
	else
		return malloc(sz);
}
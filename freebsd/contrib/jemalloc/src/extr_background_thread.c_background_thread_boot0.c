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
 scalar_t__ config_lazy_lock ; 
 int /*<<< orphan*/  have_background_thread ; 
 int /*<<< orphan*/  malloc_printf (char*) ; 
 scalar_t__ opt_background_thread ; 
 scalar_t__ pthread_create_fptr_init () ; 

bool
background_thread_boot0(void) {
	if (!have_background_thread && opt_background_thread) {
		malloc_printf("<jemalloc>: option background_thread currently "
		    "supports pthread only\n");
		return true;
	}
#ifdef JEMALLOC_PTHREAD_CREATE_WRAPPER
	if ((config_lazy_lock || opt_background_thread) &&
	    pthread_create_fptr_init()) {
		return true;
	}
#endif
	return false;
}
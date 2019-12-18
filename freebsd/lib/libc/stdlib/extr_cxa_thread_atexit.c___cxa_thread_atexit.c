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
 int __cxa_thread_atexit_hidden (void (*) (void*),void*,void*) ; 

int
__cxa_thread_atexit(void (*dtor_func)(void *), void *obj, void *dso_symbol)
{

	return (__cxa_thread_atexit_hidden(dtor_func, obj, dso_symbol));
}
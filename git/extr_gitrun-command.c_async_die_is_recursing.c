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
 int /*<<< orphan*/  async_die_counter ; 
 void* pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int async_die_is_recursing(void)
{
	void *ret = pthread_getspecific(async_die_counter);
	pthread_setspecific(async_die_counter, (void *)1);
	return ret != NULL;
}
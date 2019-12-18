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
typedef  int /*<<< orphan*/  km_flag_t ;

/* Variables and functions */
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void *
kmem_zalloc(size_t size, km_flag_t flags)
{
	void *ptr;
	ptr = malloc(size);

	memset(ptr, 0, size);

	return ptr;
}
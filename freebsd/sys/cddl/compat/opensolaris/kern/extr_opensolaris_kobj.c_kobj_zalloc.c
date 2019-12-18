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
 int /*<<< orphan*/  bzero (void*,size_t) ; 
 void* kobj_alloc (size_t,int) ; 

void *
kobj_zalloc(size_t size, int flag)
{
	void *p;

	if ((p = kobj_alloc(size, flag)) != NULL)
		bzero(p, size);
	return (p);
}
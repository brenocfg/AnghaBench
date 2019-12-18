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
 void* malloc (size_t) ; 

void *
calloc(size_t num, size_t size)
{
	void *new = malloc(num * size);
	if (!new) {
		return NULL;
	}
	bzero(new, num * size);
	return new;
}
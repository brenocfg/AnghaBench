#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t length; void** contents; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 scalar_t__ git_vector_resize_to (TYPE_1__*,size_t) ; 

int git_vector_set(void **old, git_vector *v, size_t position, void *value)
{
	if (position + 1 > v->length) {
		if (git_vector_resize_to(v, position + 1) < 0)
			return -1;
	}

	if (old != NULL)
		*old = v->contents[position];

	v->contents[position] = value;

	return 0;
}
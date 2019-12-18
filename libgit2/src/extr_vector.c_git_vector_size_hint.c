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
struct TYPE_4__ {size_t _alloc_size; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 int resize_vector (TYPE_1__*,size_t) ; 

int git_vector_size_hint(git_vector *v, size_t size_hint)
{
	if (v->_alloc_size >= size_hint)
		return 0;
	return resize_vector(v, size_hint);
}
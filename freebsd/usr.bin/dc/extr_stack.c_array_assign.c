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
struct value {int dummy; } ;
struct array {size_t size; struct value* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  array_grow (struct array*,size_t) ; 
 int /*<<< orphan*/  stack_free_value (struct value*) ; 

__attribute__((used)) static __inline void
array_assign(struct array *array, size_t i, const struct value *v)
{

	if (i >= array->size)
		array_grow(array, i + 1);
	stack_free_value(&array->data[i]);
	array->data[i] = *v;
}
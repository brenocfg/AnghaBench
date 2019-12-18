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

__attribute__((used)) static __inline struct value *
array_retrieve(const struct array *array, size_t i)
{

	if (i >= array->size)
		return (NULL);
	return &array->data[i];
}
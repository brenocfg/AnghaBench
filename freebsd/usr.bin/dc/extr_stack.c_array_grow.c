#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct array {size_t size; TYPE_1__* data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * array; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCODE_NONE ; 
 TYPE_1__* breallocarray (TYPE_1__*,size_t,int) ; 

__attribute__((used)) static __inline void
array_grow(struct array *array, size_t newsize)
{
	size_t i;

	array->data = breallocarray(array->data, newsize, sizeof(*array->data));
	for (i = array->size; i < newsize; i++) {
		array->data[i].type = BCODE_NONE;
		array->data[i].array = NULL;
	}
	array->size = newsize;
}
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
struct array {size_t size; struct array* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct array*) ; 
 int /*<<< orphan*/  stack_free_value (struct array*) ; 

__attribute__((used)) static __inline void
array_free(struct array *a)
{
	size_t i;

	if (a == NULL)
		return;
	for (i = 0; i < a->size; i++)
		stack_free_value(&a->data[i]);
	free(a->data);
	free(a);
}
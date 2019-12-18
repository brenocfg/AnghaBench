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
struct array {size_t size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  array_grow (struct array*,size_t) ; 
 struct array* array_new () ; 
 int /*<<< orphan*/  stack_dup_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct array *
array_dup(const struct array *a)
{
	struct array *n;
	size_t i;

	if (a == NULL)
		return (NULL);
	n = array_new();
	array_grow(n, a->size);
	for (i = 0; i < a->size; i++)
		stack_dup_value(&a->data[i], &n->data[i]);
	return (n);
}
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
struct ck_malloc {int /*<<< orphan*/ * free; int /*<<< orphan*/ * malloc; int /*<<< orphan*/ * realloc; } ;
struct ck_array {int /*<<< orphan*/ * transaction; struct _ck_array* active; struct ck_malloc* allocator; scalar_t__ n_entries; } ;
struct _ck_array {int dummy; } ;

/* Variables and functions */
 struct _ck_array* ck_array_create (struct ck_malloc*,unsigned int) ; 

bool
ck_array_init(struct ck_array *array, unsigned int mode, struct ck_malloc *allocator, unsigned int length)
{
	struct _ck_array *active;

	(void)mode;

	if (allocator->realloc == NULL ||
	    allocator->malloc == NULL ||
	    allocator->free == NULL ||
	    length == 0)
		return false;

	active = ck_array_create(allocator, length);
	if (active == NULL)
		return false;

	array->n_entries = 0;
	array->allocator = allocator;
	array->active = active;
	array->transaction = NULL;
	return true;
}
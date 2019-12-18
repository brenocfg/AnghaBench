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
struct ck_malloc {struct _ck_array* (* malloc ) (int) ;} ;
struct _ck_array {unsigned int length; scalar_t__ n_committed; } ;

/* Variables and functions */
 struct _ck_array* stub1 (int) ; 

__attribute__((used)) static struct _ck_array *
ck_array_create(struct ck_malloc *allocator, unsigned int length)
{
	struct _ck_array *active;

	active = allocator->malloc(sizeof(struct _ck_array) + sizeof(void *) * length);
	if (active == NULL)
		return NULL;

	active->n_committed = 0;
	active->length = length;

	return active;
}
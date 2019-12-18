#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ck_array {TYPE_2__* active; TYPE_2__* transaction; TYPE_1__* allocator; } ;
struct _ck_array {int dummy; } ;
struct TYPE_5__ {int length; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* free ) (TYPE_2__*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int,int) ; 

void
ck_array_deinit(struct ck_array *array, bool defer)
{

	array->allocator->free(array->active,
	    sizeof(struct _ck_array) + sizeof(void *) * array->active->length, defer);

	if (array->transaction != NULL) {
		array->allocator->free(array->transaction,
		    sizeof(struct _ck_array) + sizeof(void *) * array->transaction->length, defer);
	}

	array->transaction = array->active = NULL;
	return;
}
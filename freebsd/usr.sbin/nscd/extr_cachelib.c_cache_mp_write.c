#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cache_mp_write_session_ {scalar_t__ items_size; int /*<<< orphan*/  items; TYPE_3__* parent_entry; } ;
struct cache_mp_data_item_ {size_t value_size; int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {scalar_t__ max_elemsize; } ;
struct TYPE_6__ {TYPE_2__ mp_params; TYPE_1__* params; } ;
struct TYPE_4__ {scalar_t__ entry_type; } ;

/* Variables and functions */
 scalar_t__ CET_MULTIPART ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cache_mp_data_item_*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct cache_mp_write_session_*,char*,size_t)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct cache_mp_write_session_*,char*,size_t)) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct cache_mp_data_item_* calloc (int,int) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,size_t) ; 

int
cache_mp_write(struct cache_mp_write_session_ *ws, char *data,
	size_t data_size)
{
	struct cache_mp_data_item_	*new_item;

	TRACE_IN(cache_mp_write);
	assert(ws != NULL);
	assert(ws->parent_entry != NULL);
	assert(ws->parent_entry->params->entry_type == CET_MULTIPART);

	if ((ws->parent_entry->mp_params.max_elemsize > 0) &&
		(ws->parent_entry->mp_params.max_elemsize == ws->items_size)) {
		TRACE_OUT(cache_mp_write);
		return (-1);
	}

	new_item = calloc(1,
		sizeof(*new_item));
	assert(new_item != NULL);

	new_item->value = malloc(data_size);
	assert(new_item->value != NULL);
	memcpy(new_item->value, data, data_size);
	new_item->value_size = data_size;

	TAILQ_INSERT_TAIL(&ws->items, new_item, entries);
	++ws->items_size;

	TRACE_OUT(cache_mp_write);
	return (0);
}
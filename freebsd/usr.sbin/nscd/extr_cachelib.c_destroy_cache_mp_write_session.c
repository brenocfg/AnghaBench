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
struct cache_mp_write_session_ {struct cache_mp_write_session_* value; int /*<<< orphan*/  items; } ;
struct cache_mp_data_item_ {struct cache_mp_data_item_* value; int /*<<< orphan*/  items; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct cache_mp_write_session_* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cache_mp_write_session_*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_IN (void (*) (struct cache_mp_write_session_*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct cache_mp_write_session_*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (struct cache_mp_write_session_*) ; 

__attribute__((used)) static void
destroy_cache_mp_write_session(struct cache_mp_write_session_ *ws)
{

	struct cache_mp_data_item_	*data_item;

	TRACE_IN(destroy_cache_mp_write_session);
	assert(ws != NULL);
	while (!TAILQ_EMPTY(&ws->items)) {
		data_item = TAILQ_FIRST(&ws->items);
		TAILQ_REMOVE(&ws->items, data_item, entries);
		free(data_item->value);
		free(data_item);
	}

	free(ws);
	TRACE_OUT(destroy_cache_mp_write_session);
}
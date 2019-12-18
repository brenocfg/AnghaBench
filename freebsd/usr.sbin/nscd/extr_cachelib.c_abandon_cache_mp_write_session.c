#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cache_mp_write_session_ {TYPE_2__* parent_entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  ws_size; int /*<<< orphan*/  ws_head; TYPE_1__* params; } ;
struct TYPE_3__ {scalar_t__ entry_type; } ;

/* Variables and functions */
 scalar_t__ CET_MULTIPART ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cache_mp_write_session_*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_IN (void (*) (struct cache_mp_write_session_*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct cache_mp_write_session_*)) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  destroy_cache_mp_write_session (struct cache_mp_write_session_*) ; 
 int /*<<< orphan*/  entries ; 

void
abandon_cache_mp_write_session(struct cache_mp_write_session_ *ws)
{

	TRACE_IN(abandon_cache_mp_write_session);
	assert(ws != NULL);
	assert(ws->parent_entry != NULL);
	assert(ws->parent_entry->params->entry_type == CET_MULTIPART);

	TAILQ_REMOVE(&ws->parent_entry->ws_head, ws, entries);
	--ws->parent_entry->ws_size;

	destroy_cache_mp_write_session(ws);
	TRACE_OUT(abandon_cache_mp_write_session);
}
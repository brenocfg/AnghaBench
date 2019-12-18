#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct cache_mp_read_session_ {int /*<<< orphan*/  current_item; struct cache_mp_entry_* parent_entry; } ;
struct TYPE_10__ {scalar_t__ tv_sec; } ;
struct TYPE_7__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_8__ {TYPE_2__ max_lifetime; } ;
struct cache_mp_entry_ {TYPE_5__ last_request_time; int /*<<< orphan*/  (* get_time_func ) (TYPE_5__*) ;int /*<<< orphan*/  rs_size; int /*<<< orphan*/  rs_head; TYPE_4__* completed_write_session; TYPE_3__ mp_params; } ;
struct cache_entry_ {TYPE_1__* params; } ;
struct TYPE_9__ {int /*<<< orphan*/  items; } ;
struct TYPE_6__ {scalar_t__ entry_type; } ;

/* Variables and functions */
 scalar_t__ CET_MULTIPART ; 
 int /*<<< orphan*/  TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct cache_mp_read_session_*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_IN (struct cache_mp_read_session_* (*) (struct cache_entry_*)) ; 
 int /*<<< orphan*/  TRACE_OUT (struct cache_mp_read_session_* (*) (struct cache_entry_*)) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct cache_mp_read_session_* calloc (int,int) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  flush_cache_entry (struct cache_entry_*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

struct cache_mp_read_session_ *
open_cache_mp_read_session(struct cache_entry_ *entry)
{
	struct cache_mp_entry_			*mp_entry;
	struct cache_mp_read_session_	*retval;

	TRACE_IN(open_cache_mp_read_session);
	assert(entry != NULL);
	assert(entry->params->entry_type == CET_MULTIPART);
	mp_entry = (struct cache_mp_entry_ *)entry;

	if (mp_entry->completed_write_session == NULL) {
		TRACE_OUT(open_cache_mp_read_session);
		return (NULL);
	}

	if ((mp_entry->mp_params.max_lifetime.tv_sec != 0)
		|| (mp_entry->mp_params.max_lifetime.tv_usec != 0)) {
		if (mp_entry->last_request_time.tv_sec -
			mp_entry->last_request_time.tv_sec >
			mp_entry->mp_params.max_lifetime.tv_sec) {
			flush_cache_entry(entry);
			TRACE_OUT(open_cache_mp_read_session);
			return (NULL);
		}
	}

	retval = calloc(1,
		sizeof(*retval));
	assert(retval != NULL);

	retval->parent_entry = mp_entry;
	retval->current_item = TAILQ_FIRST(
		&mp_entry->completed_write_session->items);

	TAILQ_INSERT_HEAD(&mp_entry->rs_head, retval, entries);
	++mp_entry->rs_size;

	mp_entry->get_time_func(&mp_entry->last_request_time);
	TRACE_OUT(open_cache_mp_read_session);
	return (retval);
}
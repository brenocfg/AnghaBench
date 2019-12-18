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
struct cache_mp_write_session_ {struct cache_mp_entry_* parent_entry; int /*<<< orphan*/  items; } ;
struct TYPE_4__ {scalar_t__ max_sessions; } ;
struct cache_mp_entry_ {scalar_t__ ws_size; int /*<<< orphan*/  ws_head; TYPE_2__ mp_params; } ;
struct cache_entry_ {TYPE_1__* params; } ;
struct TYPE_3__ {scalar_t__ entry_type; } ;

/* Variables and functions */
 scalar_t__ CET_MULTIPART ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct cache_mp_write_session_*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_IN (struct cache_mp_write_session_* (*) (struct cache_entry_*)) ; 
 int /*<<< orphan*/  TRACE_OUT (struct cache_mp_write_session_* (*) (struct cache_entry_*)) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct cache_mp_write_session_* calloc (int,int) ; 
 int /*<<< orphan*/  entries ; 

struct cache_mp_write_session_ *
open_cache_mp_write_session(struct cache_entry_ *entry)
{
	struct cache_mp_entry_	*mp_entry;
	struct cache_mp_write_session_	*retval;

	TRACE_IN(open_cache_mp_write_session);
	assert(entry != NULL);
	assert(entry->params->entry_type == CET_MULTIPART);
	mp_entry = (struct cache_mp_entry_ *)entry;

	if ((mp_entry->mp_params.max_sessions > 0) &&
		(mp_entry->ws_size == mp_entry->mp_params.max_sessions)) {
		TRACE_OUT(open_cache_mp_write_session);
		return (NULL);
	}

	retval = calloc(1,
		sizeof(*retval));
	assert(retval != NULL);

	TAILQ_INIT(&retval->items);
	retval->parent_entry = mp_entry;

	TAILQ_INSERT_HEAD(&mp_entry->ws_head, retval, entries);
	++mp_entry->ws_size;

	TRACE_OUT(open_cache_mp_write_session);
	return (retval);
}
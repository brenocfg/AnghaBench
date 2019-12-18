#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cache_mp_read_session_ {TYPE_1__* parent_entry; } ;
struct TYPE_2__ {scalar_t__ rs_size; int /*<<< orphan*/ * pending_write_session; int /*<<< orphan*/ * completed_write_session; int /*<<< orphan*/  rs_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cache_mp_read_session_*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_IN (void (*) (struct cache_mp_read_session_*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct cache_mp_read_session_*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_cache_mp_read_session (struct cache_mp_read_session_*) ; 
 int /*<<< orphan*/  destroy_cache_mp_write_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  entries ; 

void
close_cache_mp_read_session(struct cache_mp_read_session_ *rs)
{

	TRACE_IN(close_cache_mp_read_session);
	assert(rs != NULL);
	assert(rs->parent_entry != NULL);

	TAILQ_REMOVE(&rs->parent_entry->rs_head, rs, entries);
	--rs->parent_entry->rs_size;

	if ((rs->parent_entry->rs_size == 0) &&
		(rs->parent_entry->pending_write_session != NULL)) {
		destroy_cache_mp_write_session(
			rs->parent_entry->completed_write_session);
		rs->parent_entry->completed_write_session =
			rs->parent_entry->pending_write_session;
		rs->parent_entry->pending_write_session = NULL;
	}

	destroy_cache_mp_read_session(rs);
	TRACE_OUT(close_cache_mp_read_session);
}
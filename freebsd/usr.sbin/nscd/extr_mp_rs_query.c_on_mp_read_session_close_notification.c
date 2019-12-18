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
struct query_state {int /*<<< orphan*/ * process_func; scalar_t__ kevent_watermark; int /*<<< orphan*/ * mdata; int /*<<< orphan*/  config_entry; } ;
typedef  int /*<<< orphan*/  cache_mp_read_session ;

/* Variables and functions */
 int /*<<< orphan*/  CELT_MULTIPART ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  close_cache_mp_read_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_lock_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_unlock_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
on_mp_read_session_close_notification(struct query_state *qstate)
{

	TRACE_IN(on_mp_read_session_close_notification);
	configuration_lock_entry(qstate->config_entry, CELT_MULTIPART);
	close_cache_mp_read_session((cache_mp_read_session)qstate->mdata);
	configuration_unlock_entry(qstate->config_entry, CELT_MULTIPART);
	qstate->mdata = NULL;
	qstate->kevent_watermark = 0;
	qstate->process_func = NULL;
	TRACE_OUT(on_mp_read_session_close_notification);
	return (0);
}
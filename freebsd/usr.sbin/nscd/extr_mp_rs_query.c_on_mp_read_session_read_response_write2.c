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
struct query_state {scalar_t__ (* write_func ) (struct query_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;size_t kevent_watermark; int /*<<< orphan*/  kevent_filter; int /*<<< orphan*/  process_func; int /*<<< orphan*/  response; int /*<<< orphan*/  request; } ;
struct cache_mp_read_session_read_response {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  LOG_ERR_3 (char*,char*) ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  finalize_comm_element (int /*<<< orphan*/ *) ; 
 struct cache_mp_read_session_read_response* get_cache_mp_read_session_read_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_mp_read_session_mapper ; 
 scalar_t__ stub1 (struct query_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
on_mp_read_session_read_response_write2(struct query_state *qstate)
{
	struct cache_mp_read_session_read_response *read_response;
	ssize_t	result;

	TRACE_IN(on_mp_read_session_read_response_write2);
	read_response = get_cache_mp_read_session_read_response(
		&qstate->response);
	result = qstate->write_func(qstate, read_response->data,
		read_response->data_size);
	if (result < 0 || (size_t)result != qstate->kevent_watermark) {
		LOG_ERR_3("on_mp_read_session_read_response_write2",
			"write failed");
		TRACE_OUT(on_mp_read_session_read_response_write2);
		return (-1);
	}

	finalize_comm_element(&qstate->request);
	finalize_comm_element(&qstate->response);

	qstate->kevent_watermark = sizeof(int);
	qstate->process_func = on_mp_read_session_mapper;
	qstate->kevent_filter = EVFILT_READ;

	TRACE_OUT(on_mp_read_session_read_response_write2);
	return (0);
}
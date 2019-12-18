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
struct query_state {int (* write_func ) (struct query_state*,scalar_t__*,int) ;int kevent_watermark; scalar_t__ process_func; int /*<<< orphan*/  kevent_filter; int /*<<< orphan*/  response; int /*<<< orphan*/  request; } ;
struct cache_mp_write_session_write_response {scalar_t__ error_code; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  LOG_ERR_3 (char*,char*) ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  finalize_comm_element (int /*<<< orphan*/ *) ; 
 struct cache_mp_write_session_write_response* get_cache_mp_write_session_write_response (int /*<<< orphan*/ *) ; 
 scalar_t__ on_mp_write_session_mapper ; 
 int stub1 (struct query_state*,scalar_t__*,int) ; 

__attribute__((used)) static int
on_mp_write_session_write_response_write1(struct query_state *qstate)
{
	struct cache_mp_write_session_write_response	*write_response;
	ssize_t	result;

	TRACE_IN(on_mp_write_session_write_response_write1);
	write_response = get_cache_mp_write_session_write_response(
		&qstate->response);
	result = qstate->write_func(qstate, &write_response->error_code,
		sizeof(int));
	if (result != sizeof(int)) {
		LOG_ERR_3("on_mp_write_session_write_response_write1",
			"write failed");
		TRACE_OUT(on_mp_write_session_write_response_write1);
		return (-1);
	}

	if (write_response->error_code == 0) {
		finalize_comm_element(&qstate->request);
		finalize_comm_element(&qstate->response);

		qstate->kevent_watermark = sizeof(int);
		qstate->process_func = on_mp_write_session_mapper;
		qstate->kevent_filter = EVFILT_READ;
	} else {
		qstate->kevent_watermark = 0;
		qstate->process_func = 0;
	}

	TRACE_OUT(on_mp_write_session_write_response_write1);
	return (0);
}
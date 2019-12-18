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
struct query_state {int (* read_func ) (struct query_state*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  process_func; int /*<<< orphan*/  kevent_watermark; int /*<<< orphan*/  request; } ;
struct cache_mp_write_session_write_request {int /*<<< orphan*/  data_size; int /*<<< orphan*/ * data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ BUFSIZE_INVALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CET_MP_WRITE_SESSION_WRITE_REQUEST ; 
 int /*<<< orphan*/  LOG_ERR_3 (char*,char*) ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * calloc (int,int /*<<< orphan*/ ) ; 
 struct cache_mp_write_session_write_request* get_cache_mp_write_session_write_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_comm_element (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_mp_write_session_write_request_read2 ; 
 int stub1 (struct query_state*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
on_mp_write_session_write_request_read1(struct query_state *qstate)
{
	struct cache_mp_write_session_write_request	*write_request;
	ssize_t	result;

	TRACE_IN(on_mp_write_session_write_request_read1);
	init_comm_element(&qstate->request,
		CET_MP_WRITE_SESSION_WRITE_REQUEST);
	write_request = get_cache_mp_write_session_write_request(
		&qstate->request);

	result = qstate->read_func(qstate, &write_request->data_size,
		sizeof(size_t));

	if (result != sizeof(size_t)) {
		LOG_ERR_3("on_mp_write_session_write_request_read1",
			"read failed");
		TRACE_OUT(on_mp_write_session_write_request_read1);
		return (-1);
	}

	if (BUFSIZE_INVALID(write_request->data_size)) {
		LOG_ERR_3("on_mp_write_session_write_request_read1",
			"invalid data_size value");
		TRACE_OUT(on_mp_write_session_write_request_read1);
		return (-1);
	}

	write_request->data = calloc(1, write_request->data_size);
	assert(write_request->data != NULL);

	qstate->kevent_watermark = write_request->data_size;
	qstate->process_func = on_mp_write_session_write_request_read2;
	TRACE_OUT(on_mp_write_session_write_request_read1);
	return (0);
}
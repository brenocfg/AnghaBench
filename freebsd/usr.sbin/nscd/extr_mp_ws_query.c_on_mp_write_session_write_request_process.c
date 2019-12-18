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
struct query_state {int kevent_watermark; int /*<<< orphan*/  kevent_filter; int /*<<< orphan*/  process_func; int /*<<< orphan*/  config_entry; scalar_t__ mdata; int /*<<< orphan*/  request; int /*<<< orphan*/  response; } ;
struct cache_mp_write_session_write_response {int /*<<< orphan*/  error_code; } ;
struct cache_mp_write_session_write_request {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  cache_mp_write_session ;

/* Variables and functions */
 int /*<<< orphan*/  CELT_MULTIPART ; 
 int /*<<< orphan*/  CET_MP_WRITE_SESSION_WRITE_RESPONSE ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  cache_mp_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_lock_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_unlock_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cache_mp_write_session_write_request* get_cache_mp_write_session_write_request (int /*<<< orphan*/ *) ; 
 struct cache_mp_write_session_write_response* get_cache_mp_write_session_write_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_comm_element (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_mp_write_session_write_response_write1 ; 

__attribute__((used)) static int
on_mp_write_session_write_request_process(struct query_state *qstate)
{
	struct cache_mp_write_session_write_request	*write_request;
	struct cache_mp_write_session_write_response	*write_response;

	TRACE_IN(on_mp_write_session_write_request_process);
	init_comm_element(&qstate->response,
		CET_MP_WRITE_SESSION_WRITE_RESPONSE);
	write_response = get_cache_mp_write_session_write_response(
		&qstate->response);
	write_request = get_cache_mp_write_session_write_request(
		&qstate->request);

	configuration_lock_entry(qstate->config_entry, CELT_MULTIPART);
	write_response->error_code = cache_mp_write(
		(cache_mp_write_session)qstate->mdata,
		write_request->data,
		write_request->data_size);
	configuration_unlock_entry(qstate->config_entry, CELT_MULTIPART);

	qstate->kevent_watermark = sizeof(int);
	qstate->process_func = on_mp_write_session_write_response_write1;
	qstate->kevent_filter = EVFILT_WRITE;

	TRACE_OUT(on_mp_write_session_write_request_process);
	return (0);
}
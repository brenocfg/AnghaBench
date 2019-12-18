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
struct query_state {int kevent_watermark; int /*<<< orphan*/  kevent_filter; int /*<<< orphan*/  process_func; int /*<<< orphan*/  config_entry; scalar_t__ mdata; int /*<<< orphan*/  response; } ;
struct cache_mp_read_session_read_response {scalar_t__ error_code; int /*<<< orphan*/  data_size; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  cache_mp_read_session ;

/* Variables and functions */
 int /*<<< orphan*/  CELT_MULTIPART ; 
 int /*<<< orphan*/  CET_MP_READ_SESSION_READ_RESPONSE ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int /*<<< orphan*/  TRACE_IN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_OUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* cache_mp_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configuration_lock_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_unlock_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cache_mp_read_session_read_response* get_cache_mp_read_session_read_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_comm_element (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_mp_read_session_read_response_write1 ; 
 int /*<<< orphan*/  on_mp_read_session_response_process ; 

__attribute__((used)) static int
on_mp_read_session_read_request_process(struct query_state *qstate)
{
	struct cache_mp_read_session_read_response	*read_response;

	TRACE_IN(on_mp_read_session_response_process);
	init_comm_element(&qstate->response, CET_MP_READ_SESSION_READ_RESPONSE);
	read_response = get_cache_mp_read_session_read_response(
		&qstate->response);

	configuration_lock_entry(qstate->config_entry, CELT_MULTIPART);
	read_response->error_code = cache_mp_read(
		(cache_mp_read_session)qstate->mdata, NULL,
		&read_response->data_size);

	if (read_response->error_code == 0) {
		read_response->data = malloc(read_response->data_size);
		assert(read_response != NULL);
		read_response->error_code = cache_mp_read(
			(cache_mp_read_session)qstate->mdata,
	    		read_response->data,
			&read_response->data_size);
	}
	configuration_unlock_entry(qstate->config_entry, CELT_MULTIPART);

	if (read_response->error_code == 0)
		qstate->kevent_watermark = sizeof(size_t) + sizeof(int);
	else
		qstate->kevent_watermark = sizeof(int);
	qstate->process_func = on_mp_read_session_read_response_write1;
	qstate->kevent_filter = EVFILT_WRITE;

	TRACE_OUT(on_mp_read_session_response_process);
	return (0);
}
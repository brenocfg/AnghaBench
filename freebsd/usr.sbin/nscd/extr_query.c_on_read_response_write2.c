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
struct query_state {scalar_t__ (* write_func ) (struct query_state*,int /*<<< orphan*/ ,scalar_t__) ;int kevent_watermark; int /*<<< orphan*/  process_func; int /*<<< orphan*/  kevent_filter; int /*<<< orphan*/  response; int /*<<< orphan*/  request; } ;
struct cache_read_response {scalar_t__ data_size; int /*<<< orphan*/  data; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_READ ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  finalize_comm_element (int /*<<< orphan*/ *) ; 
 struct cache_read_response* get_cache_read_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_rw_mapper ; 
 scalar_t__ stub1 (struct query_state*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
on_read_response_write2(struct query_state *qstate)
{
	struct cache_read_response	*read_response;
	ssize_t	result;

	TRACE_IN(on_read_response_write2);
	read_response = get_cache_read_response(&qstate->response);
	if (read_response->data_size > 0) {
		result = qstate->write_func(qstate, read_response->data,
			read_response->data_size);
		if (result != (ssize_t)qstate->kevent_watermark) {
			TRACE_OUT(on_read_response_write2);
			return (-1);
		}
	}

	finalize_comm_element(&qstate->request);
	finalize_comm_element(&qstate->response);

	qstate->kevent_watermark = sizeof(int);
	qstate->kevent_filter = EVFILT_READ;
	qstate->process_func = on_rw_mapper;
	TRACE_OUT(on_read_response_write2);
	return (0);
}
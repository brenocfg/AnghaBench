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
struct query_state {scalar_t__ (* write_func ) (struct query_state*,scalar_t__*,int) ;scalar_t__ kevent_watermark; int /*<<< orphan*/ * process_func; int /*<<< orphan*/  response; } ;
struct cache_read_response {scalar_t__ error_code; scalar_t__ data_size; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
 struct cache_read_response* get_cache_read_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * on_read_response_write2 ; 
 scalar_t__ stub1 (struct query_state*,scalar_t__*,int) ; 
 scalar_t__ stub2 (struct query_state*,scalar_t__*,int) ; 

__attribute__((used)) static int
on_read_response_write1(struct query_state *qstate)
{
	struct cache_read_response	*read_response;
	ssize_t	result;

	TRACE_IN(on_read_response_write1);
	read_response = get_cache_read_response(&qstate->response);

	result = qstate->write_func(qstate, &read_response->error_code,
		sizeof(int));

	if (read_response->error_code == 0) {
		result += qstate->write_func(qstate, &read_response->data_size,
			sizeof(size_t));
		if (result != (ssize_t)qstate->kevent_watermark) {
			TRACE_OUT(on_read_response_write1);
			return (-1);
		}

		qstate->kevent_watermark = read_response->data_size;
		qstate->process_func = on_read_response_write2;
	} else {
		if (result != (ssize_t)qstate->kevent_watermark) {
			TRACE_OUT(on_read_response_write1);
			return (-1);
		}

		qstate->kevent_watermark = 0;
		qstate->process_func = NULL;
	}

	TRACE_OUT(on_read_response_write1);
	return (0);
}
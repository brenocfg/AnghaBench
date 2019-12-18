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
struct query_state {scalar_t__ kevent_watermark; int (* read_func ) (struct query_state*,scalar_t__*,int) ;int /*<<< orphan*/  process_func; int /*<<< orphan*/  request; } ;
struct cache_transform_request {scalar_t__ entry_length; scalar_t__ transformation_type; int /*<<< orphan*/ * entry; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ BUFSIZE_INVALID (scalar_t__) ; 
 int /*<<< orphan*/  CET_TRANSFORM_REQUEST ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
 scalar_t__ TT_ALL ; 
 scalar_t__ TT_USER ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * calloc (int,scalar_t__) ; 
 struct cache_transform_request* get_cache_transform_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_comm_element (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_transform_request_process ; 
 int /*<<< orphan*/  on_transform_request_read2 ; 
 int stub1 (struct query_state*,scalar_t__*,int) ; 
 int stub2 (struct query_state*,scalar_t__*,int) ; 

__attribute__((used)) static int
on_transform_request_read1(struct query_state *qstate)
{
	struct cache_transform_request *transform_request;
	ssize_t	result;

	TRACE_IN(on_transform_request_read1);
	if (qstate->kevent_watermark == 0)
		qstate->kevent_watermark = sizeof(size_t) + sizeof(int);
	else {
		init_comm_element(&qstate->request, CET_TRANSFORM_REQUEST);
		transform_request =
			get_cache_transform_request(&qstate->request);

		result = qstate->read_func(qstate,
	    		&transform_request->entry_length, sizeof(size_t));
		result += qstate->read_func(qstate,
	    		&transform_request->transformation_type, sizeof(int));

		if (result != sizeof(size_t) + sizeof(int)) {
			TRACE_OUT(on_transform_request_read1);
			return (-1);
		}

		if ((transform_request->transformation_type != TT_USER) &&
		    (transform_request->transformation_type != TT_ALL)) {
			TRACE_OUT(on_transform_request_read1);
			return (-1);
		}

		if (transform_request->entry_length != 0) {
			if (BUFSIZE_INVALID(transform_request->entry_length)) {
				TRACE_OUT(on_transform_request_read1);
				return (-1);
			}

			transform_request->entry = calloc(1,
				transform_request->entry_length + 1);
			assert(transform_request->entry != NULL);

			qstate->process_func = on_transform_request_read2;
		} else
			qstate->process_func = on_transform_request_process;

		qstate->kevent_watermark = transform_request->entry_length;
	}

	TRACE_OUT(on_transform_request_read1);
	return (0);
}
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
struct query_state {scalar_t__ kevent_watermark; int (* read_func ) (struct query_state*,scalar_t__*,int) ;scalar_t__ eid_str_length; int /*<<< orphan*/  process_func; int /*<<< orphan*/  eid_str; int /*<<< orphan*/  request; } ;
struct cache_write_request {scalar_t__ entry_length; scalar_t__ cache_key_size; scalar_t__ data_size; int /*<<< orphan*/ * data; int /*<<< orphan*/ * cache_key; int /*<<< orphan*/ * entry; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ BUFSIZE_INVALID (scalar_t__) ; 
 int /*<<< orphan*/  CET_WRITE_REQUEST ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* calloc (int,scalar_t__) ; 
 struct cache_write_request* get_cache_write_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_comm_element (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  on_write_request_read2 ; 
 int stub1 (struct query_state*,scalar_t__*,int) ; 
 int stub2 (struct query_state*,scalar_t__*,int) ; 
 int stub3 (struct query_state*,scalar_t__*,int) ; 

__attribute__((used)) static int
on_write_request_read1(struct query_state *qstate)
{
	struct cache_write_request	*write_request;
	ssize_t	result;

	TRACE_IN(on_write_request_read1);
	if (qstate->kevent_watermark == 0)
		qstate->kevent_watermark = sizeof(size_t) * 3;
	else {
		init_comm_element(&qstate->request, CET_WRITE_REQUEST);
		write_request = get_cache_write_request(&qstate->request);

		result = qstate->read_func(qstate, &write_request->entry_length,
	    		sizeof(size_t));
		result += qstate->read_func(qstate,
	    		&write_request->cache_key_size, sizeof(size_t));
		result += qstate->read_func(qstate,
	    		&write_request->data_size, sizeof(size_t));

		if (result != sizeof(size_t) * 3) {
			TRACE_OUT(on_write_request_read1);
			return (-1);
		}

		if (BUFSIZE_INVALID(write_request->entry_length) ||
			BUFSIZE_INVALID(write_request->cache_key_size) ||
			(BUFSIZE_INVALID(write_request->data_size) &&
			(write_request->data_size != 0))) {
			TRACE_OUT(on_write_request_read1);
			return (-1);
		}

		write_request->entry = calloc(1,
			write_request->entry_length + 1);
		assert(write_request->entry != NULL);

		write_request->cache_key = calloc(1,
			write_request->cache_key_size +
			qstate->eid_str_length);
		assert(write_request->cache_key != NULL);
		memcpy(write_request->cache_key, qstate->eid_str,
			qstate->eid_str_length);

		if (write_request->data_size != 0) {
			write_request->data = calloc(1,
				write_request->data_size);
			assert(write_request->data != NULL);
		}

		qstate->kevent_watermark = write_request->entry_length +
			write_request->cache_key_size +
			write_request->data_size;
		qstate->process_func = on_write_request_read2;
	}

	TRACE_OUT(on_write_request_read1);
	return (0);
}
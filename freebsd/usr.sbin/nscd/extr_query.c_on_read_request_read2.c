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
struct query_state {scalar_t__ (* read_func ) (struct query_state*,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  process_func; scalar_t__ kevent_watermark; scalar_t__ eid_str_length; int /*<<< orphan*/  request; } ;
struct cache_read_request {int /*<<< orphan*/  cache_key_size; scalar_t__ cache_key; int /*<<< orphan*/  entry_length; scalar_t__ entry; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
 struct cache_read_request* get_cache_read_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_read_request_process ; 
 scalar_t__ stub1 (struct query_state*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct query_state*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
on_read_request_read2(struct query_state *qstate)
{
	struct cache_read_request	*read_request;
	ssize_t	result;

	TRACE_IN(on_read_request_read2);
	read_request = get_cache_read_request(&qstate->request);

	result = qstate->read_func(qstate, read_request->entry,
		read_request->entry_length);
	result += qstate->read_func(qstate,
		read_request->cache_key + qstate->eid_str_length,
		read_request->cache_key_size);

	if (result != (ssize_t)qstate->kevent_watermark) {
		TRACE_OUT(on_read_request_read2);
		return (-1);
	}
	read_request->cache_key_size += qstate->eid_str_length;

	qstate->kevent_watermark = 0;
	qstate->process_func = on_read_request_process;

	TRACE_OUT(on_read_request_read2);
	return (0);
}
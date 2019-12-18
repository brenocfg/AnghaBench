#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct query_state {int kevent_watermark; int /*<<< orphan*/  process_func; int /*<<< orphan*/  kevent_filter; TYPE_4__* config_entry; int /*<<< orphan*/  timeout; int /*<<< orphan*/  request; int /*<<< orphan*/  response; } ;
struct cache_write_response {int error_code; } ;
struct cache_write_request {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; int /*<<< orphan*/  cache_key_size; int /*<<< orphan*/  cache_key; int /*<<< orphan*/  entry; } ;
typedef  int /*<<< orphan*/ * cache_entry ;
struct TYPE_9__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_7__ {int /*<<< orphan*/  entry_name; } ;
struct TYPE_8__ {TYPE_1__ cep; } ;
struct TYPE_10__ {scalar_t__ enabled; scalar_t__ perform_actual_lookups; TYPE_3__ common_query_timeout; int /*<<< orphan*/ * positive_cache_entry; TYPE_2__ positive_cache_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CELT_POSITIVE ; 
 int /*<<< orphan*/  CET_WRITE_RESPONSE ; 
 int EACCES ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int /*<<< orphan*/  LOG_ERR_2 (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
 int cache_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* configuration_find_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_lock_entry (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_lock_rdlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_unlock_entry (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_cache_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cache_write_request* get_cache_write_request (int /*<<< orphan*/ *) ; 
 struct cache_write_response* get_cache_write_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_comm_element (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  on_write_response_write1 ; 
 int /*<<< orphan*/  s_cache ; 
 int /*<<< orphan*/  s_configuration ; 

__attribute__((used)) static	int
on_write_request_process(struct query_state *qstate)
{
	struct cache_write_request	*write_request;
	struct cache_write_response	*write_response;
	cache_entry c_entry;

	TRACE_IN(on_write_request_process);
	init_comm_element(&qstate->response, CET_WRITE_RESPONSE);
	write_response = get_cache_write_response(&qstate->response);
	write_request = get_cache_write_request(&qstate->request);

	qstate->config_entry = configuration_find_entry(
		s_configuration, write_request->entry);

	if (qstate->config_entry == NULL) {
		write_response->error_code = ENOENT;

		LOG_ERR_2("write_request", "can't find configuration"
		    " entry '%s'. aborting request", write_request->entry);
		goto fin;
	}

	if (qstate->config_entry->enabled == 0) {
		write_response->error_code = EACCES;

		LOG_ERR_2("write_request",
			"configuration entry '%s' is disabled",
			write_request->entry);
		goto fin;
	}

	if (qstate->config_entry->perform_actual_lookups != 0) {
		write_response->error_code = EOPNOTSUPP;

		LOG_ERR_2("write_request",
			"entry '%s' performs lookups by itself: "
			"can't write to it", write_request->entry);
		goto fin;
	}

	configuration_lock_rdlock(s_configuration);
	c_entry = find_cache_entry(s_cache,
		qstate->config_entry->positive_cache_params.cep.entry_name);
	configuration_unlock(s_configuration);
	if (c_entry != NULL) {
		configuration_lock_entry(qstate->config_entry, CELT_POSITIVE);
		qstate->config_entry->positive_cache_entry = c_entry;
		write_response->error_code = cache_write(c_entry,
			write_request->cache_key,
	    		write_request->cache_key_size,
	    		write_request->data,
			write_request->data_size);
		configuration_unlock_entry(qstate->config_entry, CELT_POSITIVE);

		if ((qstate->config_entry->common_query_timeout.tv_sec != 0) ||
		    (qstate->config_entry->common_query_timeout.tv_usec != 0))
			memcpy(&qstate->timeout,
				&qstate->config_entry->common_query_timeout,
				sizeof(struct timeval));

	} else
		write_response->error_code = -1;

fin:
	qstate->kevent_filter = EVFILT_WRITE;
	qstate->kevent_watermark = sizeof(int);
	qstate->process_func = on_write_response_write1;

	TRACE_OUT(on_write_request_process);
	return (0);
}
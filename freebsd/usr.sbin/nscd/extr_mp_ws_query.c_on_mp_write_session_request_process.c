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
struct query_state {int kevent_watermark; int /*<<< orphan*/  kevent_filter; int /*<<< orphan*/  process_func; TYPE_4__* config_entry; int /*<<< orphan*/  timeout; int /*<<< orphan*/  destroy_func; scalar_t__ mdata; int /*<<< orphan*/  eid_str; int /*<<< orphan*/  request; int /*<<< orphan*/  response; } ;
struct cache_mp_write_session_response {int error_code; } ;
struct cache_mp_write_session_request {int /*<<< orphan*/  entry; } ;
typedef  scalar_t__ cache_mp_write_session ;
typedef  int /*<<< orphan*/ * cache_entry ;
struct TYPE_9__ {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_7__ {int /*<<< orphan*/  entry_name; } ;
struct TYPE_8__ {TYPE_1__ cep; } ;
struct TYPE_10__ {scalar_t__ enabled; scalar_t__ perform_actual_lookups; TYPE_3__ mp_query_timeout; TYPE_2__ mp_cache_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CELT_MULTIPART ; 
 int /*<<< orphan*/  CET_MP_WRITE_SESSION_RESPONSE ; 
 int EACCES ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  EVFILT_WRITE ; 
 int /*<<< orphan*/ * INVALID_CACHE_ENTRY ; 
 scalar_t__ INVALID_CACHE_MP_WRITE_SESSION ; 
 int /*<<< orphan*/  LOG_ERR_2 (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ check_query_eids (struct query_state*) ; 
 TYPE_4__* configuration_find_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_lock_entry (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_lock_rdlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configuration_unlock_entry (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_cache_entry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct cache_mp_write_session_request* get_cache_mp_write_session_request (int /*<<< orphan*/ *) ; 
 struct cache_mp_write_session_response* get_cache_mp_write_session_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_comm_element (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  on_mp_write_session_destroy ; 
 int /*<<< orphan*/  on_mp_write_session_response_write1 ; 
 scalar_t__ open_cache_mp_write_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * register_new_mp_cache_entry (struct query_state*,char*) ; 
 int /*<<< orphan*/  s_cache ; 
 int /*<<< orphan*/  s_configuration ; 

__attribute__((used)) static int
on_mp_write_session_request_process(struct query_state *qstate)
{
	struct cache_mp_write_session_request	*c_mp_ws_request;
	struct cache_mp_write_session_response	*c_mp_ws_response;
	cache_mp_write_session	ws;
	cache_entry	c_entry;
	char	*dec_cache_entry_name;

	TRACE_IN(on_mp_write_session_request_process);
	init_comm_element(&qstate->response, CET_MP_WRITE_SESSION_RESPONSE);
	c_mp_ws_response = get_cache_mp_write_session_response(
		&qstate->response);
	c_mp_ws_request = get_cache_mp_write_session_request(&qstate->request);

	qstate->config_entry = configuration_find_entry(
		s_configuration, c_mp_ws_request->entry);
	if (qstate->config_entry == NULL) {
		c_mp_ws_response->error_code = ENOENT;

		LOG_ERR_2("write_session_request",
			"can't find configuration entry '%s'. "
	    		"aborting request", c_mp_ws_request->entry);
	    	goto fin;
	}

	if (qstate->config_entry->enabled == 0) {
		c_mp_ws_response->error_code = EACCES;

		LOG_ERR_2("write_session_request",
			"configuration entry '%s' is disabled",
			c_mp_ws_request->entry);
		goto fin;
	}

	if (qstate->config_entry->perform_actual_lookups != 0) {
		c_mp_ws_response->error_code = EOPNOTSUPP;

		LOG_ERR_2("write_session_request",
			"entry '%s' performs lookups by itself: "
			"can't write to it", c_mp_ws_request->entry);
		goto fin;
	} else {
#ifdef NS_NSCD_EID_CHECKING
		if (check_query_eids(qstate) != 0) {
			c_mp_ws_response->error_code = EPERM;
			goto fin;
		}
#endif
	}

	/*
	 * All multipart entries are separated by their name decorations.
	 * For one configuration entry there will be a lot of multipart
	 * cache entries - each with its own decorated name.
	 */
	asprintf(&dec_cache_entry_name, "%s%s", qstate->eid_str,
		qstate->config_entry->mp_cache_params.cep.entry_name);
	assert(dec_cache_entry_name != NULL);

	configuration_lock_rdlock(s_configuration);
	c_entry = find_cache_entry(s_cache,
		dec_cache_entry_name);
	configuration_unlock(s_configuration);

	if (c_entry == INVALID_CACHE_ENTRY)
		c_entry = register_new_mp_cache_entry(qstate,
			dec_cache_entry_name);

	free(dec_cache_entry_name);

	assert(c_entry != NULL);
	configuration_lock_entry(qstate->config_entry, CELT_MULTIPART);
	ws = open_cache_mp_write_session(c_entry);
	if (ws == INVALID_CACHE_MP_WRITE_SESSION)
		c_mp_ws_response->error_code = -1;
	else {
		qstate->mdata = ws;
		qstate->destroy_func = on_mp_write_session_destroy;

		if ((qstate->config_entry->mp_query_timeout.tv_sec != 0) ||
		    (qstate->config_entry->mp_query_timeout.tv_usec != 0))
			memcpy(&qstate->timeout,
				&qstate->config_entry->mp_query_timeout,
				sizeof(struct timeval));
	}
	configuration_unlock_entry(qstate->config_entry, CELT_MULTIPART);

fin:
	qstate->process_func = on_mp_write_session_response_write1;
	qstate->kevent_watermark = sizeof(int);
	qstate->kevent_filter = EVFILT_WRITE;

	TRACE_OUT(on_mp_write_session_request_process);
	return (0);
}
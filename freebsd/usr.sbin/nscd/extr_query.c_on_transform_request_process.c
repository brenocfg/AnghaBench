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
struct query_state {int /*<<< orphan*/  process_func; scalar_t__ kevent_watermark; struct configuration_entry* config_entry; int /*<<< orphan*/  euid; int /*<<< orphan*/  eid_str_length; int /*<<< orphan*/  eid_str; int /*<<< orphan*/  request; int /*<<< orphan*/  response; } ;
struct configuration_entry {int /*<<< orphan*/  perform_actual_lookups; } ;
struct cache_transform_response {int error_code; } ;
struct cache_transform_request {int transformation_type; int /*<<< orphan*/ * entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  CET_TRANSFORM_RESPONSE ; 
 int /*<<< orphan*/  LOG_ERR_2 (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
#define  TT_ALL 129 
#define  TT_USER 128 
 int /*<<< orphan*/  clear_config_entry (struct configuration_entry*) ; 
 int /*<<< orphan*/  clear_config_entry_part (struct configuration_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* configuration_find_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t configuration_get_entries_size (int /*<<< orphan*/ ) ; 
 struct configuration_entry* configuration_get_entry (int /*<<< orphan*/ ,size_t) ; 
 struct cache_transform_request* get_cache_transform_request (int /*<<< orphan*/ *) ; 
 struct cache_transform_response* get_cache_transform_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_comm_element (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_transform_response_write1 ; 
 int /*<<< orphan*/  s_configuration ; 

__attribute__((used)) static int
on_transform_request_process(struct query_state *qstate)
{
	struct cache_transform_request *transform_request;
	struct cache_transform_response *transform_response;
	struct configuration_entry *config_entry;
	size_t	i, size;

	TRACE_IN(on_transform_request_process);
	init_comm_element(&qstate->response, CET_TRANSFORM_RESPONSE);
	transform_response = get_cache_transform_response(&qstate->response);
	transform_request = get_cache_transform_request(&qstate->request);

	switch (transform_request->transformation_type) {
	case TT_USER:
		if (transform_request->entry == NULL) {
			size = configuration_get_entries_size(s_configuration);
			for (i = 0; i < size; ++i) {
			    config_entry = configuration_get_entry(
				s_configuration, i);

			    if (config_entry->perform_actual_lookups == 0)
			    	clear_config_entry_part(config_entry,
				    qstate->eid_str, qstate->eid_str_length);
			}
		} else {
			qstate->config_entry = configuration_find_entry(
				s_configuration, transform_request->entry);

			if (qstate->config_entry == NULL) {
				LOG_ERR_2("transform_request",
					"can't find configuration"
		   			" entry '%s'. aborting request",
					transform_request->entry);
				transform_response->error_code = -1;
				goto fin;
			}

			if (qstate->config_entry->perform_actual_lookups != 0) {
				LOG_ERR_2("transform_request",
					"can't transform the cache entry %s"
					", because it ised for actual lookups",
					transform_request->entry);
				transform_response->error_code = -1;
				goto fin;
			}

			clear_config_entry_part(qstate->config_entry,
				qstate->eid_str, qstate->eid_str_length);
		}
		break;
	case TT_ALL:
		if (qstate->euid != 0)
			transform_response->error_code = -1;
		else {
			if (transform_request->entry == NULL) {
				size = configuration_get_entries_size(
					s_configuration);
				for (i = 0; i < size; ++i) {
				    clear_config_entry(
					configuration_get_entry(
						s_configuration, i));
				}
			} else {
				qstate->config_entry = configuration_find_entry(
					s_configuration,
					transform_request->entry);

				if (qstate->config_entry == NULL) {
					LOG_ERR_2("transform_request",
						"can't find configuration"
		   				" entry '%s'. aborting request",
						transform_request->entry);
					transform_response->error_code = -1;
					goto fin;
				}

				clear_config_entry(qstate->config_entry);
			}
		}
		break;
	default:
		transform_response->error_code = -1;
	}

fin:
	qstate->kevent_watermark = 0;
	qstate->process_func = on_transform_response_write1;
	TRACE_OUT(on_transform_request_process);
	return (0);
}
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
struct comm_element {int type; int /*<<< orphan*/  c_mp_rs_read_response; int /*<<< orphan*/  c_mp_rs_response; int /*<<< orphan*/  c_mp_rs_request; int /*<<< orphan*/  c_mp_ws_write_response; int /*<<< orphan*/  c_mp_ws_write_request; int /*<<< orphan*/  c_mp_ws_response; int /*<<< orphan*/  c_mp_ws_request; int /*<<< orphan*/  c_transform_response; int /*<<< orphan*/  c_transform_request; int /*<<< orphan*/  c_read_response; int /*<<< orphan*/  c_read_request; int /*<<< orphan*/  c_write_response; int /*<<< orphan*/  c_write_request; } ;
typedef  enum comm_element_t { ____Placeholder_comm_element_t } comm_element_t ;

/* Variables and functions */
#define  CET_MP_READ_SESSION_READ_RESPONSE 141 
#define  CET_MP_READ_SESSION_REQUEST 140 
#define  CET_MP_READ_SESSION_RESPONSE 139 
#define  CET_MP_WRITE_SESSION_REQUEST 138 
#define  CET_MP_WRITE_SESSION_RESPONSE 137 
#define  CET_MP_WRITE_SESSION_WRITE_REQUEST 136 
#define  CET_MP_WRITE_SESSION_WRITE_RESPONSE 135 
#define  CET_READ_REQUEST 134 
#define  CET_READ_RESPONSE 133 
#define  CET_TRANSFORM_REQUEST 132 
#define  CET_TRANSFORM_RESPONSE 131 
#define  CET_UNDEFINED 130 
#define  CET_WRITE_REQUEST 129 
#define  CET_WRITE_RESPONSE 128 
 int /*<<< orphan*/  LOG_ERR_2 (char*,char*) ; 
 int /*<<< orphan*/  TRACE_IN (void (*) (struct comm_element*,int)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct comm_element*,int)) ; 
 int /*<<< orphan*/  init_cache_mp_read_session_read_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cache_mp_read_session_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cache_mp_read_session_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cache_mp_write_session_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cache_mp_write_session_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cache_mp_write_session_write_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cache_mp_write_session_write_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cache_read_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cache_read_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cache_transform_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cache_transform_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cache_write_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cache_write_response (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct comm_element*,int /*<<< orphan*/ ,int) ; 

void
init_comm_element(struct comm_element *element, enum comm_element_t type)
{

	TRACE_IN(init_comm_element);
	memset(element, 0, sizeof(struct comm_element));

	switch (type) {
	case CET_WRITE_REQUEST:
		init_cache_write_request(&element->c_write_request);
		break;
	case CET_WRITE_RESPONSE:
		init_cache_write_response(&element->c_write_response);
		break;
	case CET_READ_REQUEST:
		init_cache_read_request(&element->c_read_request);
		break;
	case CET_READ_RESPONSE:
		init_cache_read_response(&element->c_read_response);
		break;
	case CET_TRANSFORM_REQUEST:
		init_cache_transform_request(&element->c_transform_request);
		break;
	case CET_TRANSFORM_RESPONSE:
		init_cache_transform_response(&element->c_transform_response);
		break;
	case CET_MP_WRITE_SESSION_REQUEST:
		init_cache_mp_write_session_request(&element->c_mp_ws_request);
		break;
	case CET_MP_WRITE_SESSION_RESPONSE:
		init_cache_mp_write_session_response(&element->c_mp_ws_response);
		break;
	case CET_MP_WRITE_SESSION_WRITE_REQUEST:
		init_cache_mp_write_session_write_request(
			&element->c_mp_ws_write_request);
		break;
	case CET_MP_WRITE_SESSION_WRITE_RESPONSE:
		init_cache_mp_write_session_write_response(
			&element->c_mp_ws_write_response);
		break;
	case CET_MP_READ_SESSION_REQUEST:
		init_cache_mp_read_session_request(&element->c_mp_rs_request);
		break;
	case CET_MP_READ_SESSION_RESPONSE:
		init_cache_mp_read_session_response(&element->c_mp_rs_response);
		break;
	case CET_MP_READ_SESSION_READ_RESPONSE:
		init_cache_mp_read_session_read_response(
			&element->c_mp_rs_read_response);
		break;
	case CET_UNDEFINED:
		break;
	default:
		LOG_ERR_2("init_comm_element", "invalid communication element");
		TRACE_OUT(init_comm_element);
	return;
	}

	element->type = type;
	TRACE_OUT(init_comm_element);
}
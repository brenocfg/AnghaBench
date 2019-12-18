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
struct query_state {int kevent_watermark; int (* read_func ) (struct query_state*,int*,int) ;int /*<<< orphan*/ * process_func; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  CET_MP_WRITE_SESSION_ABANDON_NOTIFICATION 130 
#define  CET_MP_WRITE_SESSION_CLOSE_NOTIFICATION 129 
#define  CET_MP_WRITE_SESSION_WRITE_REQUEST 128 
 int /*<<< orphan*/  LOG_ERR_2 (char*,char*) ; 
 int /*<<< orphan*/  LOG_ERR_3 (char*,char*) ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (struct query_state*)) ; 
 int /*<<< orphan*/ * on_mp_write_session_abandon_notification ; 
 int /*<<< orphan*/ * on_mp_write_session_close_notification ; 
 int /*<<< orphan*/ * on_mp_write_session_write_request_read1 ; 
 int stub1 (struct query_state*,int*,int) ; 

__attribute__((used)) static int
on_mp_write_session_mapper(struct query_state *qstate)
{
	ssize_t	result;
	int		elem_type;

	TRACE_IN(on_mp_write_session_mapper);
	if (qstate->kevent_watermark == 0) {
		qstate->kevent_watermark = sizeof(int);
	} else {
		result = qstate->read_func(qstate, &elem_type, sizeof(int));
		if (result != sizeof(int)) {
			LOG_ERR_3("on_mp_write_session_mapper",
				"read failed");
			TRACE_OUT(on_mp_write_session_mapper);
			return (-1);
		}

		switch (elem_type) {
		case CET_MP_WRITE_SESSION_WRITE_REQUEST:
			qstate->kevent_watermark = sizeof(size_t);
			qstate->process_func =
				on_mp_write_session_write_request_read1;
			break;
		case CET_MP_WRITE_SESSION_ABANDON_NOTIFICATION:
			qstate->kevent_watermark = 0;
			qstate->process_func =
				on_mp_write_session_abandon_notification;
			break;
		case CET_MP_WRITE_SESSION_CLOSE_NOTIFICATION:
			qstate->kevent_watermark = 0;
			qstate->process_func =
				on_mp_write_session_close_notification;
			break;
		default:
			qstate->kevent_watermark = 0;
			qstate->process_func = NULL;
			LOG_ERR_2("on_mp_write_session_mapper",
				"unknown element type");
			TRACE_OUT(on_mp_write_session_mapper);
			return (-1);
		}
	}
	TRACE_OUT(on_mp_write_session_mapper);
	return (0);
}
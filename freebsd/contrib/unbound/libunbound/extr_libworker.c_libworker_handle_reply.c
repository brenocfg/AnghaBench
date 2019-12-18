#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct outbound_entry {int /*<<< orphan*/ * qsent; struct module_qstate* qstate; } ;
struct module_qstate {TYPE_1__* env; } ;
struct libworker {TYPE_2__* env; } ;
struct comm_reply {int dummy; } ;
struct comm_point {int /*<<< orphan*/  buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  mesh; } ;
struct TYPE_3__ {scalar_t__ worker; } ;

/* Variables and functions */
 scalar_t__ LDNS_OPCODE_WIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_PACKET_QUERY ; 
 int LDNS_QDCOUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDNS_QR_WIRE (int /*<<< orphan*/ ) ; 
 int NETEVENT_NOERROR ; 
 int NETEVENT_TIMEOUT ; 
 int /*<<< orphan*/  mesh_report_reply (int /*<<< orphan*/ ,struct outbound_entry*,struct comm_reply*,int) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ ) ; 

int 
libworker_handle_reply(struct comm_point* c, void* arg, int error,
        struct comm_reply* reply_info)
{
	struct module_qstate* q = (struct module_qstate*)arg;
	struct libworker* lw = (struct libworker*)q->env->worker;
	struct outbound_entry e;
	e.qstate = q;
	e.qsent = NULL;

	if(error != 0) {
		mesh_report_reply(lw->env->mesh, &e, reply_info, error);
		return 0;
	}
	/* sanity check. */
	if(!LDNS_QR_WIRE(sldns_buffer_begin(c->buffer))
		|| LDNS_OPCODE_WIRE(sldns_buffer_begin(c->buffer)) !=
			LDNS_PACKET_QUERY
		|| LDNS_QDCOUNT(sldns_buffer_begin(c->buffer)) > 1) {
		/* error becomes timeout for the module as if this reply
		 * never arrived. */
		mesh_report_reply(lw->env->mesh, &e, reply_info, 
			NETEVENT_TIMEOUT);
		return 0;
	}
	mesh_report_reply(lw->env->mesh, &e, reply_info, NETEVENT_NOERROR);
	return 0;
}
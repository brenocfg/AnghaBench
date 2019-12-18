#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct pending_tcp {scalar_t__ id; TYPE_1__* query; } ;
struct outside_network {int dummy; } ;
struct comm_reply {int dummy; } ;
struct comm_point {int /*<<< orphan*/  buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* cb ) (struct comm_point*,int /*<<< orphan*/ ,int,struct comm_reply*) ;int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; struct outside_network* outnet; } ;

/* Variables and functions */
 scalar_t__ LDNS_ID_WIRE (int /*<<< orphan*/ ) ; 
 int NETEVENT_CLOSED ; 
 int NETEVENT_NOERROR ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  decommission_pending_tcp (struct outside_network*,struct pending_tcp*) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_pending_tcp (int /*<<< orphan*/  (*) (struct comm_point*,int /*<<< orphan*/ ,int,struct comm_reply*)) ; 
 int /*<<< orphan*/  log_addr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ ) ; 
 int sldns_buffer_limit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct comm_point*,int /*<<< orphan*/ ,int,struct comm_reply*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 

int 
outnet_tcp_cb(struct comm_point* c, void* arg, int error,
	struct comm_reply *reply_info)
{
	struct pending_tcp* pend = (struct pending_tcp*)arg;
	struct outside_network* outnet = pend->query->outnet;
	verbose(VERB_ALGO, "outnettcp cb");
	if(error != NETEVENT_NOERROR) {
		verbose(VERB_QUERY, "outnettcp got tcp error %d", error);
		/* pass error below and exit */
	} else {
		/* check ID */
		if(sldns_buffer_limit(c->buffer) < sizeof(uint16_t) ||
			LDNS_ID_WIRE(sldns_buffer_begin(c->buffer))!=pend->id) {
			log_addr(VERB_QUERY, 
				"outnettcp: bad ID in reply, from:",
				&pend->query->addr, pend->query->addrlen);
			error = NETEVENT_CLOSED;
		}
	}
	fptr_ok(fptr_whitelist_pending_tcp(pend->query->cb));
	(void)(*pend->query->cb)(c, pend->query->cb_arg, error, reply_info);
	decommission_pending_tcp(outnet, pend);
	return 0;
}
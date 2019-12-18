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
struct worker {TYPE_2__* daemon; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_4__ {TYPE_1__* cfg; } ;
struct TYPE_3__ {scalar_t__ harden_large_queries; } ;

/* Variables and functions */
 int LDNS_ANCOUNT (int /*<<< orphan*/ ) ; 
 int LDNS_ARCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_HEADER_SIZE ; 
 int LDNS_NSCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_OPCODE_WIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_PACKET_NOTIFY ; 
 scalar_t__ LDNS_PACKET_QUERY ; 
 int LDNS_QDCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_QR_WIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDNS_RCODE_FORMERR ; 
 int /*<<< orphan*/  LDNS_RCODE_NOTIMPL ; 
 int /*<<< orphan*/  LDNS_TC_CLR (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_TC_WIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ NORMAL_UDP_SIZE ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 
 int worker_err_ratelimit (struct worker*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
worker_check_request(sldns_buffer* pkt, struct worker* worker)
{
	if(sldns_buffer_limit(pkt) < LDNS_HEADER_SIZE) {
		verbose(VERB_QUERY, "request too short, discarded");
		return -1;
	}
	if(sldns_buffer_limit(pkt) > NORMAL_UDP_SIZE && 
		worker->daemon->cfg->harden_large_queries) {
		verbose(VERB_QUERY, "request too large, discarded");
		return -1;
	}
	if(LDNS_QR_WIRE(sldns_buffer_begin(pkt))) {
		verbose(VERB_QUERY, "request has QR bit on, discarded");
		return -1;
	}
	if(LDNS_TC_WIRE(sldns_buffer_begin(pkt))) {
		LDNS_TC_CLR(sldns_buffer_begin(pkt));
		verbose(VERB_QUERY, "request bad, has TC bit on");
		return worker_err_ratelimit(worker, LDNS_RCODE_FORMERR);
	}
	if(LDNS_OPCODE_WIRE(sldns_buffer_begin(pkt)) != LDNS_PACKET_QUERY &&
		LDNS_OPCODE_WIRE(sldns_buffer_begin(pkt)) != LDNS_PACKET_NOTIFY) {
		verbose(VERB_QUERY, "request unknown opcode %d", 
			LDNS_OPCODE_WIRE(sldns_buffer_begin(pkt)));
		return worker_err_ratelimit(worker, LDNS_RCODE_NOTIMPL);
	}
	if(LDNS_QDCOUNT(sldns_buffer_begin(pkt)) != 1) {
		verbose(VERB_QUERY, "request wrong nr qd=%d", 
			LDNS_QDCOUNT(sldns_buffer_begin(pkt)));
		return worker_err_ratelimit(worker, LDNS_RCODE_FORMERR);
	}
	if(LDNS_ANCOUNT(sldns_buffer_begin(pkt)) != 0 && 
		(LDNS_ANCOUNT(sldns_buffer_begin(pkt)) != 1 ||
		LDNS_OPCODE_WIRE(sldns_buffer_begin(pkt)) != LDNS_PACKET_NOTIFY)) {
		verbose(VERB_QUERY, "request wrong nr an=%d", 
			LDNS_ANCOUNT(sldns_buffer_begin(pkt)));
		return worker_err_ratelimit(worker, LDNS_RCODE_FORMERR);
	}
	if(LDNS_NSCOUNT(sldns_buffer_begin(pkt)) != 0) {
		verbose(VERB_QUERY, "request wrong nr ns=%d", 
			LDNS_NSCOUNT(sldns_buffer_begin(pkt)));
		return worker_err_ratelimit(worker, LDNS_RCODE_FORMERR);
	}
	if(LDNS_ARCOUNT(sldns_buffer_begin(pkt)) > 1) {
		verbose(VERB_QUERY, "request wrong nr ar=%d", 
			LDNS_ARCOUNT(sldns_buffer_begin(pkt)));
		return worker_err_ratelimit(worker, LDNS_RCODE_FORMERR);
	}
	return 0;
}
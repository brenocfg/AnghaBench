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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  unwanted_queries; scalar_t__ extended; } ;
struct worker {TYPE_1__ stats; } ;
struct comm_reply {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct comm_point {int /*<<< orphan*/  buffer; } ;
typedef  enum acl_access { ____Placeholder_acl_access } acl_access ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_HEADER_SIZE ; 
 int /*<<< orphan*/  LDNS_QR_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDNS_RCODE_REFUSED ; 
 int /*<<< orphan*/  LDNS_RCODE_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  comm_point_drop_reply (struct comm_reply*) ; 
 int /*<<< orphan*/  log_addr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_buf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_set_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_write_at (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int worker_check_request (int /*<<< orphan*/ ,struct worker*) ; 

__attribute__((used)) static int
deny_refuse(struct comm_point* c, enum acl_access acl,
	enum acl_access deny, enum acl_access refuse,
	struct worker* worker, struct comm_reply* repinfo)
{
	if(acl == deny) {
		comm_point_drop_reply(repinfo);
		if(worker->stats.extended)
			worker->stats.unwanted_queries++;
		return 0;
	} else if(acl == refuse) {
		log_addr(VERB_ALGO, "refused query from",
			&repinfo->addr, repinfo->addrlen);
		log_buf(VERB_ALGO, "refuse", c->buffer);
		if(worker->stats.extended)
			worker->stats.unwanted_queries++;
		if(worker_check_request(c->buffer, worker) == -1) {
			comm_point_drop_reply(repinfo);
			return 0; /* discard this */
		}
		sldns_buffer_set_limit(c->buffer, LDNS_HEADER_SIZE);
		sldns_buffer_write_at(c->buffer, 4, 
			(uint8_t*)"\0\0\0\0\0\0\0\0", 8);
		LDNS_QR_SET(sldns_buffer_begin(c->buffer));
		LDNS_RCODE_SET(sldns_buffer_begin(c->buffer), 
			LDNS_RCODE_REFUSED);
		sldns_buffer_set_position(c->buffer, LDNS_HEADER_SIZE);
		sldns_buffer_flip(c->buffer);
		return 1;
	}

	return -1;
}
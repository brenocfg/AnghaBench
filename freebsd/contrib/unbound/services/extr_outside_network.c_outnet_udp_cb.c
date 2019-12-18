#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  key; } ;
struct pending {unsigned int id; TYPE_4__* pc; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* cb ) (struct comm_point*,int /*<<< orphan*/ ,int,struct comm_reply*) ;TYPE_1__ node; int /*<<< orphan*/  timer; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct outside_network {scalar_t__ unwanted_threshold; scalar_t__ unwanted_total; TYPE_2__* pending; int /*<<< orphan*/  unwanted_param; int /*<<< orphan*/  (* unwanted_action ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  unwanted_replies; } ;
struct comm_reply {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;
struct comm_point {int /*<<< orphan*/  buffer; } ;
struct TYPE_7__ {struct comm_point* cp; } ;
struct TYPE_6__ {scalar_t__ count; } ;

/* Variables and functions */
 scalar_t__ LDNS_HEADER_SIZE ; 
 scalar_t__ LDNS_ID_WIRE (int /*<<< orphan*/ ) ; 
 int NETEVENT_NOERROR ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  comm_timer_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_alloc_cleanup (int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  fptr_whitelist_pending_udp (int /*<<< orphan*/  (*) (struct comm_point*,int /*<<< orphan*/ ,int,struct comm_reply*)) ; 
 int /*<<< orphan*/  log_addr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (struct comm_reply*) ; 
 int /*<<< orphan*/  log_buf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warn (char*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outnet_send_wait_udp (struct outside_network*) ; 
 int /*<<< orphan*/  pending_delete (int /*<<< orphan*/ *,struct pending*) ; 
 int /*<<< orphan*/  portcomm_loweruse (struct outside_network*,TYPE_4__*) ; 
 int /*<<< orphan*/  rbtree_delete (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ rbtree_search (TYPE_2__*,struct pending*) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comm_point*,int /*<<< orphan*/ ,int,struct comm_reply*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 

int 
outnet_udp_cb(struct comm_point* c, void* arg, int error,
	struct comm_reply *reply_info)
{
	struct outside_network* outnet = (struct outside_network*)arg;
	struct pending key;
	struct pending* p;
	verbose(VERB_ALGO, "answer cb");

	if(error != NETEVENT_NOERROR) {
		verbose(VERB_QUERY, "outnetudp got udp error %d", error);
		return 0;
	}
	if(sldns_buffer_limit(c->buffer) < LDNS_HEADER_SIZE) {
		verbose(VERB_QUERY, "outnetudp udp too short");
		return 0;
	}
	log_assert(reply_info);

	/* setup lookup key */
	key.id = (unsigned)LDNS_ID_WIRE(sldns_buffer_begin(c->buffer));
	memcpy(&key.addr, &reply_info->addr, reply_info->addrlen);
	key.addrlen = reply_info->addrlen;
	verbose(VERB_ALGO, "Incoming reply id = %4.4x", key.id);
	log_addr(VERB_ALGO, "Incoming reply addr =", 
		&reply_info->addr, reply_info->addrlen);

	/* find it, see if this thing is a valid query response */
	verbose(VERB_ALGO, "lookup size is %d entries", (int)outnet->pending->count);
	p = (struct pending*)rbtree_search(outnet->pending, &key);
	if(!p) {
		verbose(VERB_QUERY, "received unwanted or unsolicited udp reply dropped.");
		log_buf(VERB_ALGO, "dropped message", c->buffer);
		outnet->unwanted_replies++;
		if(outnet->unwanted_threshold && ++outnet->unwanted_total 
			>= outnet->unwanted_threshold) {
			log_warn("unwanted reply total reached threshold (%u)"
				" you may be under attack."
				" defensive action: clearing the cache",
				(unsigned)outnet->unwanted_threshold);
			fptr_ok(fptr_whitelist_alloc_cleanup(
				outnet->unwanted_action));
			(*outnet->unwanted_action)(outnet->unwanted_param);
			outnet->unwanted_total = 0;
		}
		return 0;
	}

	verbose(VERB_ALGO, "received udp reply.");
	log_buf(VERB_ALGO, "udp message", c->buffer);
	if(p->pc->cp != c) {
		verbose(VERB_QUERY, "received reply id,addr on wrong port. "
			"dropped.");
		outnet->unwanted_replies++;
		if(outnet->unwanted_threshold && ++outnet->unwanted_total 
			>= outnet->unwanted_threshold) {
			log_warn("unwanted reply total reached threshold (%u)"
				" you may be under attack."
				" defensive action: clearing the cache",
				(unsigned)outnet->unwanted_threshold);
			fptr_ok(fptr_whitelist_alloc_cleanup(
				outnet->unwanted_action));
			(*outnet->unwanted_action)(outnet->unwanted_param);
			outnet->unwanted_total = 0;
		}
		return 0;
	}
	comm_timer_disable(p->timer);
	verbose(VERB_ALGO, "outnet handle udp reply");
	/* delete from tree first in case callback creates a retry */
	(void)rbtree_delete(outnet->pending, p->node.key);
	if(p->cb) {
		fptr_ok(fptr_whitelist_pending_udp(p->cb));
		(void)(*p->cb)(p->pc->cp, p->cb_arg, NETEVENT_NOERROR, reply_info);
	}
	portcomm_loweruse(outnet, p->pc);
	pending_delete(NULL, p);
	outnet_send_wait_udp(outnet);
	return 0;
}
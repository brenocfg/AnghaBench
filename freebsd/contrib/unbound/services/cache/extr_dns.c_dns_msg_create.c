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
typedef  void* uint16_t ;
struct ub_packed_rrset_key {int dummy; } ;
struct rrset_ref {int dummy; } ;
struct reply_info {int qdcount; struct ub_packed_rrset_key** rrsets; int /*<<< orphan*/  flags; } ;
struct regional {int dummy; } ;
struct TYPE_2__ {size_t qname_len; int /*<<< orphan*/ * local_alias; void* qclass; void* qtype; int /*<<< orphan*/  qname; } ;
struct dns_msg {struct reply_info* rep; TYPE_1__ qinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_QR ; 
 size_t RR_COUNT_MAX ; 
 scalar_t__ regional_alloc (struct regional*,size_t) ; 
 int /*<<< orphan*/  regional_alloc_init (struct regional*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ regional_alloc_zero (struct regional*,int) ; 

struct dns_msg*
dns_msg_create(uint8_t* qname, size_t qnamelen, uint16_t qtype, 
	uint16_t qclass, struct regional* region, size_t capacity)
{
	struct dns_msg* msg = (struct dns_msg*)regional_alloc(region,
		sizeof(struct dns_msg));
	if(!msg)
		return NULL;
	msg->qinfo.qname = regional_alloc_init(region, qname, qnamelen);
	if(!msg->qinfo.qname)
		return NULL;
	msg->qinfo.qname_len = qnamelen;
	msg->qinfo.qtype = qtype;
	msg->qinfo.qclass = qclass;
	msg->qinfo.local_alias = NULL;
	/* non-packed reply_info, because it needs to grow the array */
	msg->rep = (struct reply_info*)regional_alloc_zero(region, 
		sizeof(struct reply_info)-sizeof(struct rrset_ref));
	if(!msg->rep)
		return NULL;
	if(capacity > RR_COUNT_MAX)
		return NULL; /* integer overflow protection */
	msg->rep->flags = BIT_QR; /* with QR, no AA */
	msg->rep->qdcount = 1;
	msg->rep->rrsets = (struct ub_packed_rrset_key**)
		regional_alloc(region, 
		capacity*sizeof(struct ub_packed_rrset_key*));
	if(!msg->rep->rrsets)
		return NULL;
	return msg;
}
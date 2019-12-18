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
typedef  scalar_t__ uint16_t ;
struct rrset_ref {int dummy; } ;
struct reply_info {int authoritative; int qdcount; scalar_t__ flags; } ;
struct regional {int dummy; } ;
struct query_info {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct TYPE_2__ {int /*<<< orphan*/ * local_alias; int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct dns_msg {struct reply_info* rep; TYPE_1__ qinfo; } ;

/* Variables and functions */
 int BIT_AA ; 
 int BIT_QR ; 
 scalar_t__ regional_alloc (struct regional*,int) ; 
 int /*<<< orphan*/  regional_alloc_init (struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ regional_alloc_zero (struct regional*,int) ; 

__attribute__((used)) static struct dns_msg*
msg_create(struct regional* region, struct query_info* qinfo)
{
	struct dns_msg* msg = (struct dns_msg*)regional_alloc(region,
		sizeof(struct dns_msg));
	if(!msg)
		return NULL;
	msg->qinfo.qname = regional_alloc_init(region, qinfo->qname,
		qinfo->qname_len);
	if(!msg->qinfo.qname)
		return NULL;
	msg->qinfo.qname_len = qinfo->qname_len;
	msg->qinfo.qtype = qinfo->qtype;
	msg->qinfo.qclass = qinfo->qclass;
	msg->qinfo.local_alias = NULL;
	/* non-packed reply_info, because it needs to grow the array */
	msg->rep = (struct reply_info*)regional_alloc_zero(region,
		sizeof(struct reply_info)-sizeof(struct rrset_ref));
	if(!msg->rep)
		return NULL;
	msg->rep->flags = (uint16_t)(BIT_QR | BIT_AA);
	msg->rep->authoritative = 1;
	msg->rep->qdcount = 1;
	/* rrsets is NULL, no rrsets yet */
	return msg;
}
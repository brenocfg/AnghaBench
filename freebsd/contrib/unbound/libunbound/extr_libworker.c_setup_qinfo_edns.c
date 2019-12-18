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
typedef  void* uint16_t ;
struct query_info {int /*<<< orphan*/ * local_alias; int /*<<< orphan*/  qname; int /*<<< orphan*/  qname_len; void* qclass; void* qtype; } ;
struct libworker {TYPE_2__* back; } ;
struct edns_data {int edns_present; int udp_size; int /*<<< orphan*/ * opt_list; int /*<<< orphan*/  bits; scalar_t__ edns_version; scalar_t__ ext_rcode; } ;
struct ctx_query {TYPE_1__* res; } ;
struct TYPE_4__ {int /*<<< orphan*/  udp_buff; } ;
struct TYPE_3__ {int /*<<< orphan*/  qname; scalar_t__ qclass; scalar_t__ qtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDNS_DO ; 
 int sldns_buffer_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_str2wire_dname (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
setup_qinfo_edns(struct libworker* w, struct ctx_query* q, 
	struct query_info* qinfo, struct edns_data* edns)
{
	qinfo->qtype = (uint16_t)q->res->qtype;
	qinfo->qclass = (uint16_t)q->res->qclass;
	qinfo->local_alias = NULL;
	qinfo->qname = sldns_str2wire_dname(q->res->qname, &qinfo->qname_len);
	if(!qinfo->qname) {
		return 0;
	}
	qinfo->local_alias = NULL;
	edns->edns_present = 1;
	edns->ext_rcode = 0;
	edns->edns_version = 0;
	edns->bits = EDNS_DO;
	edns->opt_list = NULL;
	if(sldns_buffer_capacity(w->back->udp_buff) < 65535)
		edns->udp_size = (uint16_t)sldns_buffer_capacity(
			w->back->udp_buff);
	else	edns->udp_size = 65535;
	return 1;
}
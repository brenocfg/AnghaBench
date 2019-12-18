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
typedef  int /*<<< orphan*/  uint8_t ;
struct regional {int dummy; } ;
struct query_info {int /*<<< orphan*/ * local_alias; int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/ * qname; } ;
struct msg_parse {int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/  qname_len; scalar_t__ qname; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  dname_pkt_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 scalar_t__ regional_alloc (struct regional*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_create_qinfo(sldns_buffer* pkt, struct msg_parse* msg, 
	struct query_info* qinf, struct regional* region)
{
	if(msg->qname) {
		if(region)
			qinf->qname = (uint8_t*)regional_alloc(region, 
				msg->qname_len);
		else	qinf->qname = (uint8_t*)malloc(msg->qname_len);
		if(!qinf->qname) return 0;
		dname_pkt_copy(pkt, qinf->qname, msg->qname);
	} else	qinf->qname = 0;
	qinf->qname_len = msg->qname_len;
	qinf->qtype = msg->qtype;
	qinf->qclass = msg->qclass;
	qinf->local_alias = NULL;
	return 1;
}
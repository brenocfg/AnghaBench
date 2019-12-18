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
struct reply_info {int dummy; } ;
struct regional {int dummy; } ;
struct query_info {int /*<<< orphan*/ * local_alias; int /*<<< orphan*/ * qname; } ;
struct msg_parse {int dummy; } ;
struct edns_data {int dummy; } ;
struct alloc_cache {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int LDNS_RCODE_SERVFAIL ; 
 int /*<<< orphan*/  memset (struct msg_parse*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_create_msg (int /*<<< orphan*/ *,struct msg_parse*,struct alloc_cache*,struct query_info*,struct reply_info**,int /*<<< orphan*/ *) ; 
 int parse_extract_edns (struct msg_parse*,struct edns_data*,struct regional*) ; 
 int parse_packet (int /*<<< orphan*/ *,struct msg_parse*,struct regional*) ; 
 int /*<<< orphan*/  query_info_clear (struct query_info*) ; 
 struct msg_parse* regional_alloc (struct regional*,int) ; 
 int /*<<< orphan*/  reply_info_parsedelete (struct reply_info*,struct alloc_cache*) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int reply_info_parse(sldns_buffer* pkt, struct alloc_cache* alloc,
        struct query_info* qinf, struct reply_info** rep, 
	struct regional* region, struct edns_data* edns)
{
	/* use scratch pad region-allocator during parsing. */
	struct msg_parse* msg;
	int ret;
	
	qinf->qname = NULL;
	qinf->local_alias = NULL;
	*rep = NULL;
	if(!(msg = regional_alloc(region, sizeof(*msg)))) {
		return LDNS_RCODE_SERVFAIL;
	}
	memset(msg, 0, sizeof(*msg));
	
	sldns_buffer_set_position(pkt, 0);
	if((ret = parse_packet(pkt, msg, region)) != 0) {
		return ret;
	}
	if((ret = parse_extract_edns(msg, edns, region)) != 0)
		return ret;

	/* parse OK, allocate return structures */
	/* this also performs dname decompression */
	if(!parse_create_msg(pkt, msg, alloc, qinf, rep, NULL)) {
		query_info_clear(qinf);
		reply_info_parsedelete(*rep, alloc);
		*rep = NULL;
		return LDNS_RCODE_SERVFAIL;
	}
	return 0;
}
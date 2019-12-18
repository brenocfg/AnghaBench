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
struct query_info {int /*<<< orphan*/ * local_alias; void* qclass; void* qtype; int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_HEADER_SIZE ; 
 scalar_t__ LDNS_OPCODE_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_PACKET_NOTIFY ; 
 scalar_t__ LDNS_PACKET_QUERY ; 
 int LDNS_QDCOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  query_dname_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_current (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_position (int /*<<< orphan*/ *) ; 
 void* sldns_buffer_read_u16 (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,scalar_t__) ; 

int 
query_info_parse(struct query_info* m, sldns_buffer* query)
{
	uint8_t* q = sldns_buffer_begin(query);
	/* minimum size: header + \0 + qtype + qclass */
	if(sldns_buffer_limit(query) < LDNS_HEADER_SIZE + 5)
		return 0;
	if((LDNS_OPCODE_WIRE(q) != LDNS_PACKET_QUERY && LDNS_OPCODE_WIRE(q) !=
		LDNS_PACKET_NOTIFY) || LDNS_QDCOUNT(q) != 1 ||
		sldns_buffer_position(query) != 0)
		return 0;
	sldns_buffer_skip(query, LDNS_HEADER_SIZE);
	m->qname = sldns_buffer_current(query);
	if((m->qname_len = query_dname_len(query)) == 0)
		return 0; /* parse error */
	if(sldns_buffer_remaining(query) < 4)
		return 0; /* need qtype, qclass */
	m->qtype = sldns_buffer_read_u16(query);
	m->qclass = sldns_buffer_read_u16(query);
	m->local_alias = NULL;
	return 1;
}
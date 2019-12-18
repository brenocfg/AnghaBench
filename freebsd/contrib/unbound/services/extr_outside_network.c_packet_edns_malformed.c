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
struct sldns_buffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ LDNS_ANCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_HEADER_SIZE ; 
 int LDNS_QDCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RCODE_WIRE (int /*<<< orphan*/ ) ; 
 size_t dname_valid (scalar_t__*,scalar_t__) ; 
 scalar_t__* sldns_buffer_at (struct sldns_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_begin (struct sldns_buffer*) ; 
 scalar_t__ sldns_buffer_limit (struct sldns_buffer*) ; 

__attribute__((used)) static int
packet_edns_malformed(struct sldns_buffer* buf, int qtype)
{
	size_t len;
	if(sldns_buffer_limit(buf) < LDNS_HEADER_SIZE)
		return 1; /* malformed */
	/* they have NOERROR rcode, 1 answer. */
	if(LDNS_RCODE_WIRE(sldns_buffer_begin(buf)) != LDNS_RCODE_NOERROR)
		return 0;
	/* one query (to skip) and answer records */
	if(LDNS_QDCOUNT(sldns_buffer_begin(buf)) != 1 ||
		LDNS_ANCOUNT(sldns_buffer_begin(buf)) == 0)
		return 0;
	/* skip qname */
	len = dname_valid(sldns_buffer_at(buf, LDNS_HEADER_SIZE),
		sldns_buffer_limit(buf)-LDNS_HEADER_SIZE);
	if(len == 0)
		return 0;
	if(len == 1 && qtype == 0)
		return 0; /* we asked for '.' and type 0 */
	/* and then 4 bytes (type and class of query) */
	if(sldns_buffer_limit(buf) < LDNS_HEADER_SIZE + len + 4 + 3)
		return 0;

	/* and start with 11 zeroes as the answer RR */
	/* so check the qtype of the answer record, qname=0, type=0 */
	if(sldns_buffer_at(buf, LDNS_HEADER_SIZE+len+4)[0] == 0 &&
	   sldns_buffer_at(buf, LDNS_HEADER_SIZE+len+4)[1] == 0 &&
	   sldns_buffer_at(buf, LDNS_HEADER_SIZE+len+4)[2] == 0)
		return 1;
	return 0;
}
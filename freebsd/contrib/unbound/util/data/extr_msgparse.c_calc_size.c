#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct rr_parse {int size; } ;
typedef  int ssize_t ;
struct TYPE_3__ {scalar_t__ _dname_count; int* _wireformat; } ;
typedef  TYPE_1__ sldns_rr_descriptor ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
#define  LDNS_RDF_TYPE_DNAME 129 
#define  LDNS_RDF_TYPE_STR 128 
 size_t get_rdf_size (int) ; 
 size_t pkt_dname_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sldns_buffer_current (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_read_u16 (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* sldns_rr_descript (scalar_t__) ; 

__attribute__((used)) static int
calc_size(sldns_buffer* pkt, uint16_t type, struct rr_parse* rr)
{
	const sldns_rr_descriptor* desc;
	uint16_t pkt_len; /* length of rr inside the packet */
	rr->size = sizeof(uint16_t); /* the rdatalen */
	sldns_buffer_skip(pkt, 4); /* skip ttl */
	pkt_len = sldns_buffer_read_u16(pkt);
	if(sldns_buffer_remaining(pkt) < pkt_len)
		return 0;
	desc = sldns_rr_descript(type);
	if(pkt_len > 0 && desc && desc->_dname_count > 0) {
		int count = (int)desc->_dname_count;
		int rdf = 0;
		size_t len;
		size_t oldpos;
		/* skip first part. */
		while(pkt_len > 0 && count) {
			switch(desc->_wireformat[rdf]) {
			case LDNS_RDF_TYPE_DNAME:
				/* decompress every domain name */
				oldpos = sldns_buffer_position(pkt);
				if((len = pkt_dname_len(pkt)) == 0)
					return 0; /* malformed dname */
				if(sldns_buffer_position(pkt)-oldpos > pkt_len)
					return 0; /* dname exceeds rdata */
				pkt_len -= sldns_buffer_position(pkt)-oldpos;
				rr->size += len;
				count--;
				len = 0;
				break;
			case LDNS_RDF_TYPE_STR:
				if(pkt_len < 1) {
					/* NOTREACHED, due to 'while(>0)' */
					return 0; /* len byte exceeds rdata */
				}
				len = sldns_buffer_current(pkt)[0] + 1;
				break;
			default:
				len = get_rdf_size(desc->_wireformat[rdf]);
			}
			if(len) {
				if(pkt_len < len)
					return 0; /* exceeds rdata */
				pkt_len -= len;
				sldns_buffer_skip(pkt, (ssize_t)len);
				rr->size += len;
			}
			rdf++;
		}
	}
	/* remaining rdata */
	rr->size += pkt_len;
	sldns_buffer_skip(pkt, (ssize_t)pkt_len);
	return 1;
}
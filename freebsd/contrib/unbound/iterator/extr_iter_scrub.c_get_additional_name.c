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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct rrset_parse {int type; } ;
struct rr_parse {int /*<<< orphan*/ * ttl_data; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
#define  LDNS_RR_TYPE_KX 135 
#define  LDNS_RR_TYPE_MB 134 
#define  LDNS_RR_TYPE_MD 133 
#define  LDNS_RR_TYPE_MF 132 
#define  LDNS_RR_TYPE_MX 131 
#define  LDNS_RR_TYPE_NAPTR 130 
#define  LDNS_RR_TYPE_NS 129 
#define  LDNS_RR_TYPE_SRV 128 
 size_t pkt_dname_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,size_t) ; 
 size_t sldns_read_uint16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_additional_name(struct rrset_parse* rrset, struct rr_parse* rr, 
	uint8_t** nm, size_t* nmlen, sldns_buffer* pkt) 
{
	size_t offset = 0;
	size_t len, oldpos;
	switch(rrset->type) {
		case LDNS_RR_TYPE_MB:
		case LDNS_RR_TYPE_MD:
		case LDNS_RR_TYPE_MF:
		case LDNS_RR_TYPE_NS:
			offset = 0;
			break;
		case LDNS_RR_TYPE_MX:
		case LDNS_RR_TYPE_KX:
			offset = 2;
			break;
		case LDNS_RR_TYPE_SRV:
			offset = 6;
			break;
		case LDNS_RR_TYPE_NAPTR:
			/* TODO: NAPTR not supported, glue stripped off */
			return 0;
		default:
			return 0;
	}
	len = sldns_read_uint16(rr->ttl_data+sizeof(uint32_t));
	if(len < offset+1)
		return 0; /* rdata field too small */
	*nm = rr->ttl_data+sizeof(uint32_t)+sizeof(uint16_t)+offset;
	oldpos = sldns_buffer_position(pkt);
	sldns_buffer_set_position(pkt, (size_t)(*nm - sldns_buffer_begin(pkt)));
	*nmlen = pkt_dname_len(pkt);
	sldns_buffer_set_position(pkt, oldpos);
	if(*nmlen == 0)
		return 0;
	return 1;
}
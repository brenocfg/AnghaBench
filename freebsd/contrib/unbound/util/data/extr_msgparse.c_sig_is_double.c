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
typedef  int uint16_t ;
struct rrset_parse {struct rr_parse* rrsig_first; } ;
struct rr_parse {struct rr_parse* next; scalar_t__ ttl_data; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  siglen ;

/* Variables and functions */
 scalar_t__ memcmp (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int*,scalar_t__,int) ; 
 int ntohs (int) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int sldns_buffer_read_u16 (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
sig_is_double(sldns_buffer* pkt, struct rrset_parse* rrset, uint8_t* ttldata)
{
	uint16_t rlen, siglen;
	size_t pos = sldns_buffer_position(pkt);
	struct rr_parse* sig;
	if(sldns_buffer_remaining(pkt) < 6) 
		return 0;
	sldns_buffer_skip(pkt, 4); /* ttl */
	rlen = sldns_buffer_read_u16(pkt);
	if(sldns_buffer_remaining(pkt) < rlen) {
		sldns_buffer_set_position(pkt, pos);
		return 0;
	}
	sldns_buffer_set_position(pkt, pos);

	sig = rrset->rrsig_first;
	while(sig) {
		/* check if rdatalen is same */
		memmove(&siglen, sig->ttl_data+4, sizeof(siglen));
		siglen = ntohs(siglen);
		/* checks if data in packet is exactly the same, this means
		 * also dname in rdata is the same, but rrsig is not allowed
		 * to have compressed dnames anyway. If it is compressed anyway
		 * it will lead to duplicate rrs for qtype=RRSIG. (or ANY).
		 *
		 * Cannot use sig->size because size of the other one is not 
		 * calculated yet.
		 */
		if(siglen == rlen) {
			if(siglen>0 && memcmp(sig->ttl_data+6, ttldata+6, 
				siglen) == 0) {
				/* same! */
				return 1;
			}
		}
		sig = sig->next;
	}
	return 0;
}
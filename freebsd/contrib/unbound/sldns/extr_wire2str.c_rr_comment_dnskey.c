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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int LDNS_KEY_SEP_KEY ; 
 int LDNS_KEY_ZONE_KEY ; 
 int /*<<< orphan*/  sldns_calc_keytag_raw (scalar_t__*,size_t) ; 
 size_t sldns_read_uint16 (scalar_t__*) ; 
 scalar_t__ sldns_rr_dnskey_key_size_raw (unsigned char*,size_t,int) ; 
 scalar_t__ sldns_str_print (char**,size_t*,char*,...) ; 

__attribute__((used)) static int rr_comment_dnskey(char** s, size_t* slen, uint8_t* rr,
	size_t rrlen, size_t dname_off)
{
	size_t rdlen;
	uint8_t* rdata;
	int flags, w = 0;
	if(rrlen < dname_off + 10) return 0;
	rdlen = sldns_read_uint16(rr+dname_off+8);
	if(rrlen < dname_off + 10 + rdlen) return 0;
	rdata = rr + dname_off + 10;
	flags = (int)sldns_read_uint16(rdata);
	w += sldns_str_print(s, slen, " ;{");

	/* id */
	w += sldns_str_print(s, slen, "id = %u",
		sldns_calc_keytag_raw(rdata, rdlen));

	/* flags */
	if((flags&LDNS_KEY_ZONE_KEY)) {
		if((flags&LDNS_KEY_SEP_KEY))
			w += sldns_str_print(s, slen, " (ksk)");
		else 	w += sldns_str_print(s, slen, " (zsk)");
	}

	/* keysize */
	if(rdlen > 4) {
		w += sldns_str_print(s, slen, ", ");
		w += sldns_str_print(s, slen, "size = %db",
			(int)sldns_rr_dnskey_key_size_raw(
			(unsigned char*)rdata+4, rdlen-4, (int)(rdata[3])));
	}

	w += sldns_str_print(s, slen, "}");
	return w;
}
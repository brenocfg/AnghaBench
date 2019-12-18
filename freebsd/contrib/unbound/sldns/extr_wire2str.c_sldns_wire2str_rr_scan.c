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
typedef  void* uint16_t ;

/* Variables and functions */
 void* LDNS_RR_TYPE_OPT ; 
 scalar_t__ print_remainder_hex (char*,scalar_t__**,size_t*,char**,size_t*) ; 
 void* sldns_read_uint16 (scalar_t__*) ; 
 scalar_t__ sldns_rr_tcttl_scan (scalar_t__**,size_t*,char**,size_t*) ; 
 int sldns_str_print (char**,size_t*,char*,...) ; 
 scalar_t__ sldns_wire2str_class_print (char**,size_t*,void*) ; 
 scalar_t__ sldns_wire2str_dname_scan (scalar_t__**,size_t*,char**,size_t*,scalar_t__*,size_t) ; 
 int sldns_wire2str_edns_scan (scalar_t__**,size_t*,char**,size_t*,scalar_t__*,size_t) ; 
 scalar_t__ sldns_wire2str_rdata_scan (scalar_t__**,size_t*,char**,size_t*,void*,scalar_t__*,size_t) ; 
 scalar_t__ sldns_wire2str_rr_comment_print (char**,size_t*,scalar_t__*,size_t,size_t,void*) ; 
 scalar_t__ sldns_wire2str_type_print (char**,size_t*,void*) ; 

int sldns_wire2str_rr_scan(uint8_t** d, size_t* dlen, char** s, size_t* slen,
	uint8_t* pkt, size_t pktlen)
{
	int w = 0;
	uint8_t* rr = *d;
	size_t rrlen = *dlen, dname_off, rdlen, ordlen;
	uint16_t rrtype = 0;
	
	if(*dlen >= 3 && (*d)[0]==0 &&
		sldns_read_uint16((*d)+1)==LDNS_RR_TYPE_OPT) {
		/* perform EDNS OPT processing */
		return sldns_wire2str_edns_scan(d, dlen, s, slen, pkt, pktlen);
	}

	/* try to scan the rdata with pretty-printing, but if that fails, then
	 * scan the rdata as an unknown RR type */
	w += sldns_wire2str_dname_scan(d, dlen, s, slen, pkt, pktlen);
	w += sldns_str_print(s, slen, "\t");
	dname_off = rrlen-(*dlen);
	if(*dlen == 4) {
		/* like a question-RR */
		uint16_t t = sldns_read_uint16(*d);
		uint16_t c = sldns_read_uint16((*d)+2);
		(*d)+=4;
		(*dlen)-=4;
		w += sldns_wire2str_class_print(s, slen, c);
		w += sldns_str_print(s, slen, "\t");
		w += sldns_wire2str_type_print(s, slen, t);
		w += sldns_str_print(s, slen, " ; Error no ttl,rdata\n");
		return w;
	}
	if(*dlen < 8) {
		if(*dlen == 0)
			return w + sldns_str_print(s, slen, ";Error missing RR\n");
		w += print_remainder_hex(";Error partial RR 0x", d, dlen, s, slen);
		return w + sldns_str_print(s, slen, "\n");
	}
	rrtype = sldns_read_uint16(*d);
	w += sldns_rr_tcttl_scan(d, dlen, s, slen);
	w += sldns_str_print(s, slen, "\t");

	/* rdata */
	if(*dlen < 2) {
		if(*dlen == 0)
			return w + sldns_str_print(s, slen, ";Error missing rdatalen\n");
		w += print_remainder_hex(";Error missing rdatalen 0x",
			d, dlen, s, slen);
		return w + sldns_str_print(s, slen, "\n");
	}
	rdlen = sldns_read_uint16(*d);
	ordlen = rdlen;
	(*d)+=2;
	(*dlen)-=2;
	if(*dlen < rdlen) {
		w += sldns_str_print(s, slen, "\\# %u ", (unsigned)rdlen);
		if(*dlen == 0)
			return w + sldns_str_print(s, slen, ";Error missing rdata\n");
		w += print_remainder_hex(";Error partial rdata 0x", d, dlen, s, slen);
		return w + sldns_str_print(s, slen, "\n");
	}
	w += sldns_wire2str_rdata_scan(d, &rdlen, s, slen, rrtype, pkt, pktlen);
	(*dlen) -= (ordlen-rdlen);

	/* default comment */
	w += sldns_wire2str_rr_comment_print(s, slen, rr, rrlen, dname_off,
		rrtype);
	w += sldns_str_print(s, slen, "\n");
	return w;
}
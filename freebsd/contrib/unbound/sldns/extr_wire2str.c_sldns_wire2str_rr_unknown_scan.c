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

/* Variables and functions */
 scalar_t__ print_remainder_hex (char*,int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 size_t sldns_read_uint16 (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_rr_tcttl_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_str_print (char**,size_t*,char*,...) ; 
 scalar_t__ sldns_wire2str_dname_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ sldns_wire2str_rdata_unknown_scan (int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 

int sldns_wire2str_rr_unknown_scan(uint8_t** d, size_t* dlen, char** s,
	size_t* slen, uint8_t* pkt, size_t pktlen)
{
	size_t rdlen, ordlen;
	int w = 0;
	w += sldns_wire2str_dname_scan(d, dlen, s, slen, pkt, pktlen);
	w += sldns_str_print(s, slen, "\t");
	w += sldns_rr_tcttl_scan(d, dlen, s, slen);
	w += sldns_str_print(s, slen, "\t");
	if(*dlen < 2) {
		if(*dlen == 0)
			return w + sldns_str_print(s, slen, ";Error missing rdatalen\n");
		w += print_remainder_hex(";Error missing rdatalen 0x",
			d, dlen, s, slen);
		return w + sldns_str_print(s, slen, "\n");
	}
	rdlen = sldns_read_uint16(*d);
	ordlen = rdlen;
	(*d) += 2;
	(*dlen) -= 2;
	if(*dlen < rdlen) {
		w += sldns_str_print(s, slen, "\\# %u ", (unsigned)rdlen);
		if(*dlen == 0)
			return w + sldns_str_print(s, slen, ";Error missing rdata\n");
		w += print_remainder_hex(";Error partial rdata 0x", d, dlen, s, slen);
		return w + sldns_str_print(s, slen, "\n");
	}
	w += sldns_wire2str_rdata_unknown_scan(d, &rdlen, s, slen);
	(*dlen) -= (ordlen-rdlen);
	w += sldns_str_print(s, slen, "\n");
	return w;
}
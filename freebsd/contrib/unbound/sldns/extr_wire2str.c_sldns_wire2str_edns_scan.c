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
typedef  int uint16_t ;

/* Variables and functions */
 int LDNS_EDNS_MASK_DO_BIT ; 
 size_t LDNS_HEADER_SIZE ; 
 int LDNS_RCODE_WIRE (scalar_t__*) ; 
 scalar_t__ LDNS_RR_TYPE_OPT ; 
 scalar_t__ print_edns_opts (char**,size_t*,scalar_t__*,int) ; 
 int print_remainder_hex (char*,scalar_t__**,size_t*,char**,size_t*) ; 
 scalar_t__ sldns_read_uint16 (scalar_t__*) ; 
 scalar_t__ sldns_str_print (char**,size_t*,char*,...) ; 

int sldns_wire2str_edns_scan(uint8_t** data, size_t* data_len, char** str,
        size_t* str_len, uint8_t* pkt, size_t pktlen)
{
	int w = 0;
	uint8_t ext_rcode, edns_version;
	uint16_t udpsize, edns_bits, rdatalen;
	w += sldns_str_print(str, str_len, "; EDNS:");

	/* some input checks, domain name */
	if(*data_len < 1+10)
		return w + print_remainder_hex("Error malformed 0x",
			data, data_len, str, str_len);
	if(*data[0] != 0) {
		return w + print_remainder_hex("Error nonrootdname 0x",
			data, data_len, str, str_len);
	}
	(*data)++;
	(*data_len)--;

	/* check type and read fixed contents */
	if(sldns_read_uint16((*data)) != LDNS_RR_TYPE_OPT) {
		return w + print_remainder_hex("Error nottypeOPT 0x",
			data, data_len, str, str_len);
	}
	udpsize = sldns_read_uint16((*data)+2);
	ext_rcode = (*data)[4];
	edns_version = (*data)[5];
	edns_bits = sldns_read_uint16((*data)+6);
	rdatalen = sldns_read_uint16((*data)+8);
	(*data)+=10;
	(*data_len)-=10;

	w += sldns_str_print(str, str_len, " version: %u;",
		(unsigned)edns_version);
	w += sldns_str_print(str, str_len, " flags:");
	if((edns_bits & LDNS_EDNS_MASK_DO_BIT))
		w += sldns_str_print(str, str_len, " do");
	/* the extended rcode is the value set, shifted four bits,
	 * and or'd with the original rcode */
	if(ext_rcode) {
		int rc = ((int)ext_rcode)<<4;
		if(pkt && pktlen >= LDNS_HEADER_SIZE)
			rc |= LDNS_RCODE_WIRE(pkt);
		w += sldns_str_print(str, str_len, " ; ext-rcode: %d", rc);
	}
	w += sldns_str_print(str, str_len, " ; udp: %u", (unsigned)udpsize);

	if(rdatalen) {
		if((size_t)*data_len < rdatalen) {
			w += sldns_str_print(str, str_len,
				" ; Error EDNS rdata too short; ");
			rdatalen = (uint16_t)*data_len;
		}
		w += print_edns_opts(str, str_len, *data, rdatalen);
		(*data) += rdatalen;
		(*data_len) -= rdatalen;
	}
	w += sldns_str_print(str, str_len, "\n");
	return w;
}
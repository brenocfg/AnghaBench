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
 scalar_t__ LDNS_AA_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_AD_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_ANCOUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_ARCOUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_CD_WIRE (int /*<<< orphan*/ *) ; 
 size_t LDNS_HEADER_SIZE ; 
 scalar_t__ LDNS_ID_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_NSCOUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_OPCODE_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_QDCOUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_QR_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_RA_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_RCODE_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_RD_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_TC_WIRE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_Z_WIRE (int /*<<< orphan*/ *) ; 
 int print_remainder_hex (char*,int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int sldns_str_print (char**,size_t*,char*,...) ; 
 scalar_t__ sldns_wire2str_opcode_print (char**,size_t*,int) ; 
 scalar_t__ sldns_wire2str_rcode_print (char**,size_t*,int) ; 

int sldns_wire2str_header_scan(uint8_t** d, size_t* dlen, char** s,
	size_t* slen)
{
	int w = 0;
	int opcode, rcode;
	w += sldns_str_print(s, slen, ";; ->>HEADER<<- ");
	if(*dlen == 0)
		return w+sldns_str_print(s, slen, "Error empty packet");
	if(*dlen < 4)
		return w+print_remainder_hex("Error header too short 0x", d, dlen, s, slen);
	opcode = (int)LDNS_OPCODE_WIRE(*d);
	rcode = (int)LDNS_RCODE_WIRE(*d);
	w += sldns_str_print(s, slen, "opcode: ");
	w += sldns_wire2str_opcode_print(s, slen, opcode);
	w += sldns_str_print(s, slen, ", ");
	w += sldns_str_print(s, slen, "rcode: ");
	w += sldns_wire2str_rcode_print(s, slen, rcode);
	w += sldns_str_print(s, slen, ", ");
	w += sldns_str_print(s, slen, "id: %d\n", (int)LDNS_ID_WIRE(*d));
	w += sldns_str_print(s, slen, ";; flags:");
	if(LDNS_QR_WIRE(*d)) w += sldns_str_print(s, slen, " qr");
	if(LDNS_AA_WIRE(*d)) w += sldns_str_print(s, slen, " aa");
	if(LDNS_TC_WIRE(*d)) w += sldns_str_print(s, slen, " tc");
	if(LDNS_RD_WIRE(*d)) w += sldns_str_print(s, slen, " rd");
	if(LDNS_CD_WIRE(*d)) w += sldns_str_print(s, slen, " cd");
	if(LDNS_RA_WIRE(*d)) w += sldns_str_print(s, slen, " ra");
	if(LDNS_AD_WIRE(*d)) w += sldns_str_print(s, slen, " ad");
	if(LDNS_Z_WIRE(*d))  w += sldns_str_print(s, slen, " z");
	w += sldns_str_print(s, slen, " ; ");
	if(*dlen < LDNS_HEADER_SIZE)
		return w+print_remainder_hex("Error header too short 0x", d, dlen, s, slen);
	w += sldns_str_print(s, slen, "QUERY: %d, ", (int)LDNS_QDCOUNT(*d));
	w += sldns_str_print(s, slen, "ANSWER: %d, ", (int)LDNS_ANCOUNT(*d));
	w += sldns_str_print(s, slen, "AUTHORITY: %d, ", (int)LDNS_NSCOUNT(*d));
	w += sldns_str_print(s, slen, "ADDITIONAL: %d ", (int)LDNS_ARCOUNT(*d));
	*d += LDNS_HEADER_SIZE;
	*dlen -= LDNS_HEADER_SIZE;
	return w;
}
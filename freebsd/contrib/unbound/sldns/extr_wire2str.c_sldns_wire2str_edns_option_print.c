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

/* Variables and functions */
#define  LDNS_EDNS_CLIENT_SUBNET 136 
#define  LDNS_EDNS_DAU 135 
#define  LDNS_EDNS_DHU 134 
#define  LDNS_EDNS_KEEPALIVE 133 
#define  LDNS_EDNS_LLQ 132 
#define  LDNS_EDNS_N3U 131 
#define  LDNS_EDNS_NSID 130 
#define  LDNS_EDNS_PADDING 129 
#define  LDNS_EDNS_UL 128 
 int print_hex_buf (char**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ sldns_str_print (char**,size_t*,char*) ; 
 int sldns_wire2str_edns_dau_print (char**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 int sldns_wire2str_edns_dhu_print (char**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 int sldns_wire2str_edns_keepalive_print (char**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 int sldns_wire2str_edns_llq_print (char**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 int sldns_wire2str_edns_n3u_print (char**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 int sldns_wire2str_edns_nsid_print (char**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ sldns_wire2str_edns_option_code_print (char**,size_t*,int) ; 
 int sldns_wire2str_edns_subnet_print (char**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 int sldns_wire2str_edns_ul_print (char**,size_t*,int /*<<< orphan*/ *,size_t) ; 

int sldns_wire2str_edns_option_print(char** s, size_t* sl,
	uint16_t option_code, uint8_t* optdata, size_t optlen)
{
	int w = 0;
	w += sldns_wire2str_edns_option_code_print(s, sl, option_code);
	w += sldns_str_print(s, sl, ": ");
	switch(option_code) {
	case LDNS_EDNS_LLQ:
		w += sldns_wire2str_edns_llq_print(s, sl, optdata, optlen);
		break;
	case LDNS_EDNS_UL:
		w += sldns_wire2str_edns_ul_print(s, sl, optdata, optlen);
		break;
	case LDNS_EDNS_NSID:
		w += sldns_wire2str_edns_nsid_print(s, sl, optdata, optlen);
		break;
	case LDNS_EDNS_DAU:
		w += sldns_wire2str_edns_dau_print(s, sl, optdata, optlen);
		break;
	case LDNS_EDNS_DHU:
		w += sldns_wire2str_edns_dhu_print(s, sl, optdata, optlen);
		break;
	case LDNS_EDNS_N3U:
		w += sldns_wire2str_edns_n3u_print(s, sl, optdata, optlen);
		break;
	case LDNS_EDNS_CLIENT_SUBNET:
		w += sldns_wire2str_edns_subnet_print(s, sl, optdata, optlen);
		break;
	 case LDNS_EDNS_KEEPALIVE:
		w += sldns_wire2str_edns_keepalive_print(s, sl, optdata, optlen);
		break;
	case LDNS_EDNS_PADDING:
		w += print_hex_buf(s, sl, optdata, optlen);
		break;
	default:
		/* unknown option code */
		w += print_hex_buf(s, sl, optdata, optlen);
		break;
	}
	return w;
}
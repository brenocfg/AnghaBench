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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ print_hex_buf (char**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ sldns_read_uint16 (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_str_print (char**,size_t*,char*) ; 
 scalar_t__ sldns_wire2str_edns_option_code_print (char**,size_t*,scalar_t__) ; 
 scalar_t__ sldns_wire2str_edns_option_print (char**,size_t*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
print_edns_opts(char** s, size_t* sl, uint8_t* rdata, size_t rdatalen)
{
	uint16_t option_code, option_len;
	int w = 0;
	while(rdatalen > 0) {
		/* option name */
		if(rdatalen < 4) {
			w += sldns_str_print(s, sl, " ; malformed: ");
			w += print_hex_buf(s, sl, rdata, rdatalen);
			return w;
		}
		option_code = sldns_read_uint16(rdata);
		option_len = sldns_read_uint16(rdata+2);
		rdata += 4;
		rdatalen -= 4;

		/* option value */
		if(rdatalen < (size_t)option_len) {
			w += sldns_str_print(s, sl, " ; malformed ");
			w += sldns_wire2str_edns_option_code_print(s, sl,
				option_code);
			w += sldns_str_print(s, sl, ": ");
			w += print_hex_buf(s, sl, rdata, rdatalen);
			return w;
		}
		w += sldns_str_print(s, sl, " ; ");
		w += sldns_wire2str_edns_option_print(s, sl, option_code,
			rdata, option_len);
		rdata += option_len;
		rdatalen -= option_len;
	}
	return w;
}
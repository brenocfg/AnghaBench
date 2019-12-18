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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ print_hex_buf (char**,size_t*,scalar_t__*,scalar_t__) ; 
 scalar_t__ sldns_read_uint16 (scalar_t__*) ; 
 int sldns_str_print (char**,size_t*,char*,...) ; 
 scalar_t__ sldns_wire2str_b64_scan_num (scalar_t__**,size_t*,char**,size_t*,scalar_t__) ; 

int sldns_wire2str_hip_scan(uint8_t** d, size_t* dl, char** s, size_t* sl)
{
	int w;
	uint8_t algo, hitlen;
	uint16_t pklen;

	/* read lengths */
	if(*dl < 4)
		return -1;
	hitlen = (*d)[0];
	algo = (*d)[1];
	pklen = sldns_read_uint16((*d)+2);
	if(*dl < (size_t)4 + (size_t)hitlen + (size_t)pklen)
		return -1;

	/* write: algo hit pubkey */
	w = sldns_str_print(s, sl, "%u ", (unsigned)algo);
	w += print_hex_buf(s, sl, (*d)+4, hitlen);
	w += sldns_str_print(s, sl, " ");
	(*d)+=4+hitlen;
	(*dl)-= (4+hitlen);
	w += sldns_wire2str_b64_scan_num(d, dl, s, sl, pklen);
	return w;
}
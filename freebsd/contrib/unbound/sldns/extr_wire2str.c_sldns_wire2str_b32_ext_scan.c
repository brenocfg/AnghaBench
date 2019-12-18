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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t sldns_b32_ntop_calculate_size (size_t) ; 
 int /*<<< orphan*/  sldns_b32_ntop_extended_hex (size_t*,size_t,char*,size_t) ; 

int sldns_wire2str_b32_ext_scan(uint8_t** d, size_t* dl, char** s, size_t* sl)
{
	size_t datalen;
	size_t sz;
	if(*dl < 1) return -1;
	datalen = (*d)[0];
	if(*dl < 1+datalen) return -1;
	sz = sldns_b32_ntop_calculate_size(datalen);
	if(*sl < sz+1) {
		(*d) += datalen+1;
		(*dl) -= (datalen+1);
		return (int)sz; /* out of space really, but would need buffer
			in order to truncate the output */
	}
	sldns_b32_ntop_extended_hex((*d)+1, datalen, *s, *sl);
	(*d) += datalen+1;
	(*dl) -= (datalen+1);
	(*s) += sz;
	(*sl) -= sz;
	return (int)sz;
}
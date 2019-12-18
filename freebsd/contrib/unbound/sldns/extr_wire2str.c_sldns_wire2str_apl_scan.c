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
typedef  int uint8_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ LDNS_APL_IP4 ; 
 scalar_t__ LDNS_APL_IP6 ; 
 int LDNS_APL_MASK ; 
 int LDNS_APL_NEGATION ; 
 scalar_t__ sldns_read_uint16 (int*) ; 
 scalar_t__ sldns_str_print (char**,size_t*,char*,...) ; 

int sldns_wire2str_apl_scan(uint8_t** d, size_t* dl, char** s, size_t* sl)
{
	int i, w = 0;
	uint16_t family;
	uint8_t negation, prefix, adflength;
	if(*dl < 4) return -1;
	family = sldns_read_uint16(*d);
	prefix = (*d)[2];
	negation = ((*d)[3] & LDNS_APL_NEGATION);
	adflength = ((*d)[3] & LDNS_APL_MASK);
	if(*dl < 4+(size_t)adflength) return -1;
	if(family != LDNS_APL_IP4 && family != LDNS_APL_IP6)
		return -1; /* unknown address family */
	if(negation)
		w += sldns_str_print(s, sl, "!");
	w += sldns_str_print(s, sl, "%u:", (unsigned)family);
	if(family == LDNS_APL_IP4) {
		/* check if prefix <32 ? */
		/* address is variable length 0 - 4 */
		for(i=0; i<4; i++) {
			if(i > 0)
				w += sldns_str_print(s, sl, ".");
			if(i < (int)adflength)
				w += sldns_str_print(s, sl, "%d", (*d)[4+i]);
			else	w += sldns_str_print(s, sl, "0");
		}
	} else if(family == LDNS_APL_IP6) {
		/* check if prefix <128 ? */
		/* address is variable length 0 - 16 */
		for(i=0; i<16; i++) {
			if(i%2 == 0 && i>0)
				w += sldns_str_print(s, sl, ":");
			if(i < (int)adflength)
				w += sldns_str_print(s, sl, "%02x", (*d)[4+i]);
			else	w += sldns_str_print(s, sl, "00");
		}
	}
	w += sldns_str_print(s, sl, "/%u", (unsigned)prefix);
	(*d) += 4+adflength;
	(*dl) -= 4+adflength;
	return w;
}
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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int print_remainder_hex (char*,int /*<<< orphan*/ **,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  sldns_read_uint16 (int /*<<< orphan*/ *) ; 
 int sldns_wire2str_class_print (char**,size_t*,int /*<<< orphan*/ ) ; 

int sldns_wire2str_class_scan(uint8_t** d, size_t* dlen, char** s, size_t* slen)
{
	uint16_t c;
	if(*dlen == 0) return 0;
	if(*dlen < 2) return print_remainder_hex("Error malformed 0x", d, dlen, s, slen);
	c = sldns_read_uint16(*d);
	(*d)+=2;
	(*dlen)-=2;
	return sldns_wire2str_class_print(s, slen, c);
}
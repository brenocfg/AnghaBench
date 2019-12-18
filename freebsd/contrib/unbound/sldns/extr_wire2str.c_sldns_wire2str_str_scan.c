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
 scalar_t__ sldns_str_print (char**,size_t*,char*) ; 
 scalar_t__ str_char_print (char**,size_t*,size_t) ; 

int sldns_wire2str_str_scan(uint8_t** d, size_t* dl, char** s, size_t* sl)
{
	int w = 0;
	size_t i, len;
	if(*dl < 1) return -1;
	len = **d;
	if(*dl < 1+len) return -1;
	(*d)++;
	(*dl)--;
	w += sldns_str_print(s, sl, "\"");
	for(i=0; i<len; i++)
		w += str_char_print(s, sl, (*d)[i]);
	w += sldns_str_print(s, sl, "\"");
	(*d)+=len;
	(*dl)-=len;
	return w;
}
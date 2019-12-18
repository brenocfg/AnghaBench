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
 scalar_t__ sldns_str_print (char**,size_t*,char*) ; 
 scalar_t__ str_char_print (char**,size_t*,int /*<<< orphan*/ ) ; 

int sldns_wire2str_long_str_scan(uint8_t** d, size_t* dl, char** s, size_t* sl)
{
	size_t i;
	int w = 0;
	w += sldns_str_print(s, sl, "\"");
	for(i=0; i<*dl; i++)
		w += str_char_print(s, sl, (*d)[i]);
	w += sldns_str_print(s, sl, "\"");
	(*d)+=*dl;
	(*dl)=0;
	return w;
}
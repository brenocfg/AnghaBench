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

/* Variables and functions */
 int sldns_str_print (char**,size_t*,char*,unsigned int) ; 

int sldns_wire2str_int8_scan(uint8_t** d, size_t* dl, char** s, size_t* sl)
{
	int w;
	if(*dl < 1) return -1;
	w = sldns_str_print(s, sl, "%u", (unsigned)**d);
	(*d)++;
	(*dl)--;
	return w;
}
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

/* Variables and functions */
 scalar_t__ sldns_str_print (char**,size_t*,char*,...) ; 

int sldns_wire2str_edns_n3u_print(char** s, size_t* sl, uint8_t* data,
	size_t len)
{
	size_t i;
	int w = 0;
	for(i=0; i<len; i++) {
		if(data[i] == 1)
			w += sldns_str_print(s, sl, " SHA1");
		else 	w += sldns_str_print(s, sl, " %d", (int)data[i]);
	}
	return w;
}
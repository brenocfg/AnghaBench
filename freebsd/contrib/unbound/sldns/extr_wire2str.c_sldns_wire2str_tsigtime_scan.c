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
typedef  int uint64_t ;

/* Variables and functions */
 int sldns_str_print (char**,size_t*,char*,long long) ; 

int sldns_wire2str_tsigtime_scan(uint8_t** d, size_t* dl, char** s, size_t* sl)
{
	/* tsigtime is 48 bits network order unsigned integer */
	int w;
	uint64_t tsigtime = 0;
	uint64_t d0, d1, d2, d3, d4, d5;
	if(*dl < 6) return -1;
	d0 = (*d)[0]; /* cast to uint64 for shift operations */
	d1 = (*d)[1];
	d2 = (*d)[2];
	d3 = (*d)[3];
	d4 = (*d)[4];
	d5 = (*d)[5];
	tsigtime = (d0<<40) | (d1<<32) | (d2<<24) | (d3<<16) | (d4<<8) | d5;
#ifndef USE_WINSOCK
	w = sldns_str_print(s, sl, "%llu", (long long)tsigtime);
#else
	w = sldns_str_print(s, sl, "%I64u", (long long)tsigtime);
#endif
	(*d)+=6;
	(*dl)-=6;
	return w;
}
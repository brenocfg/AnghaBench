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
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int sldns_str_print (char**,size_t*,char*,char*) ; 

int sldns_wire2str_aaaa_scan(uint8_t** d, size_t* dl, char** s, size_t* sl)
{
#ifdef AF_INET6
	char buf[64];
	int w;
	if(*dl < 16) return -1;
	if(!inet_ntop(AF_INET6, *d, buf, (socklen_t)sizeof(buf)))
		return -1;
	w = sldns_str_print(s, sl, "%s", buf);
	(*d)+=16;
	(*dl)-=16;
	return w;
#else
	return -1;
#endif
}
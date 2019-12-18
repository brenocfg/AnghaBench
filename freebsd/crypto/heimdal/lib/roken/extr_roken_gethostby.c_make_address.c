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
struct in_addr {unsigned char s_addr; } ;
struct hostent {scalar_t__ h_addr; } ;

/* Variables and functions */
 struct hostent* gethostbyname (char const*) ; 
 scalar_t__ inet_aton (char const*,struct in_addr*) ; 

__attribute__((used)) static int
make_address(const char *address, struct in_addr *ip)
{
    if(inet_aton(address, ip) == 0){
	/* try to resolve as hostname, it might work if the address we
           are trying to lookup is local, for instance a web proxy */
	struct hostent *he = gethostbyname(address);
	if(he) {
	    unsigned char *p = (unsigned char*)he->h_addr;
	    ip->s_addr = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
	} else {
	    return -1;
	}
    }
    return 0;
}
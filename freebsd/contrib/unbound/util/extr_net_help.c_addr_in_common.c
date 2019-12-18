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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ addr_is_ip6 (struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (int) ; 

int
addr_in_common(struct sockaddr_storage* addr1, int net1,
	struct sockaddr_storage* addr2, int net2, socklen_t addrlen)
{
	int min = (net1<net2)?net1:net2;
	int i, to;
	int match = 0;
	uint8_t* s1, *s2;
	if(addr_is_ip6(addr1, addrlen)) {
		s1 = (uint8_t*)&((struct sockaddr_in6*)addr1)->sin6_addr;
		s2 = (uint8_t*)&((struct sockaddr_in6*)addr2)->sin6_addr;
		to = 16;
	} else {
		s1 = (uint8_t*)&((struct sockaddr_in*)addr1)->sin_addr;
		s2 = (uint8_t*)&((struct sockaddr_in*)addr2)->sin_addr;
		to = 4;
	}
	/* match = bits_in_common(s1, s2, to); */
	for(i=0; i<to; i++) {
		if(s1[i] == s2[i]) {
			match += 8;
		} else {
			uint8_t z = s1[i]^s2[i];
			log_assert(z);
			while(!(z&0x80)) {
				match++;
				z<<=1;
			}
			break;
		}
	}
	if(match > min) match = min;
	return match;
}
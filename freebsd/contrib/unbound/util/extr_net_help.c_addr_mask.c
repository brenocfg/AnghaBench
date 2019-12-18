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

void
addr_mask(struct sockaddr_storage* addr, socklen_t len, int net)
{
	uint8_t mask[8] = {0x0, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe};
	int i, max;
	uint8_t* s;
	if(addr_is_ip6(addr, len)) {
		s = (uint8_t*)&((struct sockaddr_in6*)addr)->sin6_addr;
		max = 128;
	} else {
		s = (uint8_t*)&((struct sockaddr_in*)addr)->sin_addr;
		max = 32;
	}
	if(net >= max)
		return;
	for(i=net/8+1; i<max/8; i++) {
		s[i] = 0;
	}
	s[net/8] &= mask[net&0x7];
}
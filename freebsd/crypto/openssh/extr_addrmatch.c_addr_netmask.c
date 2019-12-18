#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_2__ {void* s_addr; } ;
struct xaddr {int af; int* addr32; TYPE_1__ v4; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 void* htonl (int) ; 
 scalar_t__ masklen_valid (int,int) ; 
 int /*<<< orphan*/  memset (struct xaddr*,char,int) ; 

__attribute__((used)) static int
addr_netmask(int af, u_int l, struct xaddr *n)
{
	int i;

	if (masklen_valid(af, l) != 0 || n == NULL)
		return -1;

	memset(n, '\0', sizeof(*n));
	switch (af) {
	case AF_INET:
		n->af = AF_INET;
		if (l == 0)
			return 0;
		n->v4.s_addr = htonl((0xffffffff << (32 - l)) & 0xffffffff);
		return 0;
	case AF_INET6:
		n->af = AF_INET6;
		for (i = 0; i < 4 && l >= 32; i++, l -= 32)
			n->addr32[i] = 0xffffffffU;
		if (i < 4 && l != 0)
			n->addr32[i] = htonl((0xffffffff << (32 - l)) &
			    0xffffffff);
		return 0;
	default:
		return -1;
	}
}
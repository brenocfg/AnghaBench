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
typedef  int u_int ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 

__attribute__((used)) static inline int
masklen_valid(int af, u_int masklen)
{
	switch (af) {
	case AF_INET:
		return masklen <= 32 ? 0 : -1;
	case AF_INET6:
		return masklen <= 128 ? 0 : -1;
	default:
		return -1;
	}
}
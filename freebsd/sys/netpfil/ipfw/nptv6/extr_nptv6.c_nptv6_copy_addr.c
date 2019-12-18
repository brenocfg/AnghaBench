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
struct in6_addr {int* s6_addr8; } ;

/* Variables and functions */

__attribute__((used)) static void
nptv6_copy_addr(struct in6_addr *src, struct in6_addr *dst,
    struct in6_addr *mask)
{
	int i;

	for (i = 0; i < 8 && mask->s6_addr8[i] != 0; i++) {
		dst->s6_addr8[i] &=  ~mask->s6_addr8[i];
		dst->s6_addr8[i] |= src->s6_addr8[i] & mask->s6_addr8[i];
	}
}
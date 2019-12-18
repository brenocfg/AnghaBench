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
typedef  int uint8_t ;
struct ub_randstate {int dummy; } ;
struct TYPE_2__ {int* s6_addr; } ;
struct sockaddr_in6 {TYPE_1__ sin6_addr; } ;

/* Variables and functions */
 int ub_random_max (struct ub_randstate*,int) ; 

__attribute__((used)) static void
sai6_putrandom(struct sockaddr_in6 *sa, int pfxlen, struct ub_randstate *rnd)
{
	int i, last;
	if(!(pfxlen > 0 && pfxlen < 128))
		return;
	for(i = 0; i < (128 - pfxlen) / 8; i++) {
		sa->sin6_addr.s6_addr[15-i] = (uint8_t)ub_random_max(rnd, 256);
	}
	last = pfxlen & 7;
	if(last != 0) {
		sa->sin6_addr.s6_addr[15-i] |=
			((0xFF >> last) & ub_random_max(rnd, 256));
	}
}
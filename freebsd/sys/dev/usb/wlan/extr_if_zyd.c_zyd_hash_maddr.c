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
typedef  int uint32_t ;
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 scalar_t__ LLADDR (struct sockaddr_dl*) ; 

__attribute__((used)) static u_int
zyd_hash_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	uint32_t *hash = arg;
	uint8_t v;

	v = ((uint8_t *)LLADDR(sdl))[5] >> 2;
	if (v < 32)
		hash[0] |= 1 << v;
	else
		hash[1] |= 1 << (v - 32);

	return (1);
}
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
typedef  int uint32_t ;
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int ether_crc32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
gem_hash_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	uint32_t crc, *hash = arg;

	crc = ether_crc32_le(LLADDR(sdl), ETHER_ADDR_LEN);
	/* We just want the 8 most significant bits. */
	crc >>= 24;
	/* Set the corresponding bit in the filter. */
	hash[crc >> 4] |= 1 << (15 - (crc & 15));

	return (1);
}
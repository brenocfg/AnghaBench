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
 int ether_crc32_be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
tsec_hash_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	uint32_t h, *hashtable = arg;

	h = (ether_crc32_be(LLADDR(sdl), ETHER_ADDR_LEN) >> 24) & 0xFF;
	hashtable[(h >> 5)] |= 1 << (0x1F - (h & 0x1F));

	return (1);
}
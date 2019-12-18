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
et_hash_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	uint32_t h, *hp, *hash = arg;

	h = ether_crc32_be(LLADDR(sdl), ETHER_ADDR_LEN);
	h = (h & 0x3f800000) >> 23;

	hp = &hash[0];
	if (h >= 32 && h < 64) {
		h -= 32;
		hp = &hash[1];
	} else if (h >= 64 && h < 96) {
		h -= 64;
		hp = &hash[2];
	} else if (h >= 96) {
		h -= 96;
		hp = &hash[3];
	}
	*hp |= (1 << h);

	return (1);
}
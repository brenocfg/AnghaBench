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
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int dc_mchash_be (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
dc_hash_maddr_admtek_be(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	uint32_t *hashes = arg;
	int h = 0;

	h = dc_mchash_be(LLADDR(sdl));
	if (h < 32)
		hashes[0] |= (1 << h);
	else
		hashes[1] |= (1 << (h - 32));

	return (1);
}
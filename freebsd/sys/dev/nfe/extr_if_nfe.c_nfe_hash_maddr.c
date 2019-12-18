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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;
struct nfe_hash_maddr_ctx {int /*<<< orphan*/ * mask; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/ * LLADDR (struct sockaddr_dl*) ; 

__attribute__((used)) static u_int
nfe_hash_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct nfe_hash_maddr_ctx *ctx = arg;
	uint8_t *addrp, mcaddr;
	int j;

	addrp = LLADDR(sdl);
	for (j = 0; j < ETHER_ADDR_LEN; j++) {
		mcaddr = addrp[j];
		ctx->addr[j] &= mcaddr;
		ctx->mask[j] &= ~mcaddr;
	}

	return (1);
}
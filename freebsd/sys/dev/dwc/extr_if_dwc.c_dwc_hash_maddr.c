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
typedef  int uint32_t ;
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;
struct dwc_hash_maddr_ctx {int* hash; TYPE_1__* sc; } ;
struct TYPE_2__ {scalar_t__ mactype; } ;

/* Variables and functions */
 scalar_t__ DWC_GMAC_ALT_DESC ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int bitreverse (int) ; 
 int ether_crc32_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
dwc_hash_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct dwc_hash_maddr_ctx *ctx = arg;
	uint32_t crc, hashbit, hashreg;
	uint8_t val;

	crc = ether_crc32_le(LLADDR(sdl), ETHER_ADDR_LEN);
	/* Take lower 8 bits and reverse it */
	val = bitreverse(~crc & 0xff);
	if (ctx->sc->mactype == DWC_GMAC_ALT_DESC)
		val >>= 2; /* Only need lower 6 bits */
	hashreg = (val >> 5);
	hashbit = (val & 31);
	ctx->hash[hashreg] |= (1 << hashbit);

	return (1);
}
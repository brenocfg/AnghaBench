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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ u_int ;
struct sockaddr_dl {int dummy; } ;
struct sk_add_maddr_genesis_ctx {int* hashes; int /*<<< orphan*/  mode; int /*<<< orphan*/  sc_if; } ;

/* Variables and functions */
 scalar_t__ LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  XM_MODE_RX_USE_HASH ; 
 int /*<<< orphan*/  XM_MODE_RX_USE_PERFECT ; 
 scalar_t__ XM_RXFILT_MAX ; 
 int /*<<< orphan*/  sk_setfilt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int sk_xmchash (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static u_int
sk_add_maddr_genesis(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct sk_add_maddr_genesis_ctx *ctx = arg;
	int h;

	/*
	 * Program the first XM_RXFILT_MAX multicast groups
	 * into the perfect filter.
	 */
	if (cnt + 1 < XM_RXFILT_MAX) {
		sk_setfilt(ctx->sc_if, (uint16_t *)LLADDR(sdl), cnt + 1);
		ctx->mode |= XM_MODE_RX_USE_PERFECT;
		return (1);
	}
	h = sk_xmchash((const uint8_t *)LLADDR(sdl));
	if (h < 32)
		ctx->hashes[0] |= (1 << h);
	else
		ctx->hashes[1] |= (1 << (h - 32));
	ctx->mode |= XM_MODE_RX_USE_HASH;

	return (1);
}
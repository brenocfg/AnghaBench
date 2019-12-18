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
typedef  int u_int ;
struct sockaddr_dl {int dummy; } ;
struct dc_hash_maddr_admtek_le_ctx {int* hashes; int /*<<< orphan*/  sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int dc_mchash_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
dc_hash_maddr_admtek_le(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct dc_hash_maddr_admtek_le_ctx *ctx = arg;
	int h = 0;

	h = dc_mchash_le(ctx->sc, LLADDR(sdl));
	if (h < 32)
		ctx->hashes[0] |= (1 << h);
	else
		ctx->hashes[1] |= (1 << (h - 32));

	return (1);
}
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
struct trad_enc_ctx {long* keys; } ;

/* Variables and functions */
 void* CRC32 (long,int) ; 

__attribute__((used)) static void
trad_enc_update_keys(struct trad_enc_ctx *ctx, uint8_t c)
{
	uint8_t t;
#define CRC32(c, b) (crc32(c ^ 0xffffffffUL, &b, 1) ^ 0xffffffffUL)

	ctx->keys[0] = CRC32(ctx->keys[0], c);
	ctx->keys[1] = (ctx->keys[1] + (ctx->keys[0] & 0xff)) * 134775813L + 1;
	t = (ctx->keys[1] >> 24) & 0xff;
	ctx->keys[2] = CRC32(ctx->keys[2], t);
#undef CRC32
}
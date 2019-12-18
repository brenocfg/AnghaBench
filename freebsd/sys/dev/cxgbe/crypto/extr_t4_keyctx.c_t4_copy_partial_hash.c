#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * state; } ;
struct TYPE_11__ {int /*<<< orphan*/ * state; } ;
struct TYPE_10__ {int /*<<< orphan*/ * state; } ;
struct TYPE_9__ {int /*<<< orphan*/ * state; } ;
struct TYPE_7__ {int /*<<< orphan*/ * b32; } ;
struct TYPE_8__ {TYPE_1__ h; } ;
union authctx {TYPE_6__ sha512ctx; TYPE_5__ sha384ctx; TYPE_4__ sha256ctx; TYPE_3__ sha224ctx; TYPE_2__ sha1ctx; } ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;

/* Variables and functions */
#define  CRYPTO_SHA1 137 
#define  CRYPTO_SHA1_HMAC 136 
#define  CRYPTO_SHA2_224 135 
#define  CRYPTO_SHA2_224_HMAC 134 
#define  CRYPTO_SHA2_256 133 
#define  CRYPTO_SHA2_256_HMAC 132 
#define  CRYPTO_SHA2_384 131 
#define  CRYPTO_SHA2_384_HMAC 130 
#define  CRYPTO_SHA2_512 129 
#define  CRYPTO_SHA2_512_HMAC 128 
 int SHA1_HASH_LEN ; 
 int SHA2_256_HASH_LEN ; 
 int SHA2_512_HASH_LEN ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe64 (int /*<<< orphan*/ ) ; 

void
t4_copy_partial_hash(int alg, union authctx *auth_ctx, void *dst)
{
	uint32_t *u32;
	uint64_t *u64;
	u_int i;

	u32 = (uint32_t *)dst;
	u64 = (uint64_t *)dst;
	switch (alg) {
	case CRYPTO_SHA1:
	case CRYPTO_SHA1_HMAC:
		for (i = 0; i < SHA1_HASH_LEN / 4; i++)
			u32[i] = htobe32(auth_ctx->sha1ctx.h.b32[i]);
		break;
	case CRYPTO_SHA2_224:
	case CRYPTO_SHA2_224_HMAC:
		for (i = 0; i < SHA2_256_HASH_LEN / 4; i++)
			u32[i] = htobe32(auth_ctx->sha224ctx.state[i]);
		break;
	case CRYPTO_SHA2_256:
	case CRYPTO_SHA2_256_HMAC:
		for (i = 0; i < SHA2_256_HASH_LEN / 4; i++)
			u32[i] = htobe32(auth_ctx->sha256ctx.state[i]);
		break;
	case CRYPTO_SHA2_384:
	case CRYPTO_SHA2_384_HMAC:
		for (i = 0; i < SHA2_512_HASH_LEN / 8; i++)
			u64[i] = htobe64(auth_ctx->sha384ctx.state[i]);
		break;
	case CRYPTO_SHA2_512:
	case CRYPTO_SHA2_512_HMAC:
		for (i = 0; i < SHA2_512_HASH_LEN / 8; i++)
			u64[i] = htobe64(auth_ctx->sha512ctx.state[i]);
		break;
	}
}
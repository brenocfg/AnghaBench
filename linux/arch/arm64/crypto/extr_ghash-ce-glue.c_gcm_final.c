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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {void* b; void* a; } ;
typedef  TYPE_1__ u128 ;
struct gcm_aes_ctx {int /*<<< orphan*/  ghash_key; } ;
struct aead_request {int assoclen; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 void* cpu_to_be64 (int) ; 
 int /*<<< orphan*/  crypto_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ghash_do_update (int,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmull_ghash_update_p64 ; 
 int /*<<< orphan*/  put_unaligned_be64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gcm_final(struct aead_request *req, struct gcm_aes_ctx *ctx,
		      u64 dg[], u8 tag[], int cryptlen)
{
	u8 mac[AES_BLOCK_SIZE];
	u128 lengths;

	lengths.a = cpu_to_be64(req->assoclen * 8);
	lengths.b = cpu_to_be64(cryptlen * 8);

	ghash_do_update(1, dg, (void *)&lengths, &ctx->ghash_key, NULL,
			pmull_ghash_update_p64);

	put_unaligned_be64(dg[1], mac);
	put_unaligned_be64(dg[0], mac + 8);

	crypto_xor(tag, mac, AES_BLOCK_SIZE);
}
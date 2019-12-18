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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {void** token; int /*<<< orphan*/  options; } ;
struct safexcel_command_desc {TYPE_1__ control_data; } ;
struct safexcel_cipher_ctx {scalar_t__ mode; scalar_t__ xcm; int alg; void* nonce; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD ; 
 scalar_t__ CONTEXT_CONTROL_CRYPTO_MODE_ECB ; 
 int DES3_EDE_BLOCK_SIZE ; 
 int DES_BLOCK_SIZE ; 
 int /*<<< orphan*/  EIP197_OPTION_2_TOKEN_IV_CMD ; 
 int /*<<< orphan*/  EIP197_OPTION_4_TOKEN_IV_CMD ; 
 scalar_t__ EIP197_XCM_MODE_CCM ; 
 scalar_t__ EIP197_XCM_MODE_GCM ; 
#define  SAFEXCEL_3DES 130 
#define  SAFEXCEL_AES 129 
#define  SAFEXCEL_DES 128 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (void**,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void safexcel_cipher_token(struct safexcel_cipher_ctx *ctx, u8 *iv,
				  struct safexcel_command_desc *cdesc)
{
	u32 block_sz = 0;

	if (ctx->mode == CONTEXT_CONTROL_CRYPTO_MODE_CTR_LOAD) {
		cdesc->control_data.options |= EIP197_OPTION_4_TOKEN_IV_CMD;

		/* 32 bit nonce */
		cdesc->control_data.token[0] = ctx->nonce;
		/* 64 bit IV part */
		memcpy(&cdesc->control_data.token[1], iv, 8);
		/* 32 bit counter, start at 1 (big endian!) */
		cdesc->control_data.token[3] = cpu_to_be32(1);

		return;
	} else if (ctx->xcm == EIP197_XCM_MODE_GCM) {
		cdesc->control_data.options |= EIP197_OPTION_4_TOKEN_IV_CMD;

		/* 96 bit IV part */
		memcpy(&cdesc->control_data.token[0], iv, 12);
		/* 32 bit counter, start at 1 (big endian!) */
		cdesc->control_data.token[3] = cpu_to_be32(1);

		return;
	} else if (ctx->xcm == EIP197_XCM_MODE_CCM) {
		cdesc->control_data.options |= EIP197_OPTION_4_TOKEN_IV_CMD;

		/* Variable length IV part */
		memcpy(&cdesc->control_data.token[0], iv, 15 - iv[0]);
		/* Start variable length counter at 0 */
		memset((u8 *)&cdesc->control_data.token[0] + 15 - iv[0],
		       0, iv[0] + 1);

		return;
	}

	if (ctx->mode != CONTEXT_CONTROL_CRYPTO_MODE_ECB) {
		switch (ctx->alg) {
		case SAFEXCEL_DES:
			block_sz = DES_BLOCK_SIZE;
			cdesc->control_data.options |= EIP197_OPTION_2_TOKEN_IV_CMD;
			break;
		case SAFEXCEL_3DES:
			block_sz = DES3_EDE_BLOCK_SIZE;
			cdesc->control_data.options |= EIP197_OPTION_2_TOKEN_IV_CMD;
			break;
		case SAFEXCEL_AES:
			block_sz = AES_BLOCK_SIZE;
			cdesc->control_data.options |= EIP197_OPTION_4_TOKEN_IV_CMD;
			break;
		}
		memcpy(cdesc->control_data.token, iv, block_sz);
	}
}
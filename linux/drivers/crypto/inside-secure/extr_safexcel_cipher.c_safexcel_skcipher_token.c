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
typedef  int /*<<< orphan*/  u32 ;
struct safexcel_token {int stat; int instructions; int /*<<< orphan*/  packet_length; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {scalar_t__ token; } ;
struct safexcel_command_desc {TYPE_1__ control_data; } ;
struct safexcel_cipher_ctx {int dummy; } ;

/* Variables and functions */
 int EIP197_TOKEN_INS_LAST ; 
 int EIP197_TOKEN_INS_TYPE_CRYPTO ; 
 int EIP197_TOKEN_INS_TYPE_OUTPUT ; 
 int /*<<< orphan*/  EIP197_TOKEN_OPCODE_DIRECTION ; 
 int EIP197_TOKEN_STAT_LAST_HASH ; 
 int EIP197_TOKEN_STAT_LAST_PACKET ; 
 int /*<<< orphan*/  safexcel_cipher_token (struct safexcel_cipher_ctx*,int /*<<< orphan*/ *,struct safexcel_command_desc*) ; 

__attribute__((used)) static void safexcel_skcipher_token(struct safexcel_cipher_ctx *ctx, u8 *iv,
				    struct safexcel_command_desc *cdesc,
				    u32 length)
{
	struct safexcel_token *token;

	safexcel_cipher_token(ctx, iv, cdesc);

	/* skip over worst case IV of 4 dwords, no need to be exact */
	token = (struct safexcel_token *)(cdesc->control_data.token + 4);

	token[0].opcode = EIP197_TOKEN_OPCODE_DIRECTION;
	token[0].packet_length = length;
	token[0].stat = EIP197_TOKEN_STAT_LAST_PACKET |
			EIP197_TOKEN_STAT_LAST_HASH;
	token[0].instructions = EIP197_TOKEN_INS_LAST |
				EIP197_TOKEN_INS_TYPE_CRYPTO |
				EIP197_TOKEN_INS_TYPE_OUTPUT;
}
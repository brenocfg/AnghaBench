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
typedef  int uint16_t ;
struct aes_cbc_mac_ctx {int /*<<< orphan*/  keysched; int /*<<< orphan*/  rounds; } ;

/* Variables and functions */
 int /*<<< orphan*/  rijndaelKeySetupEnc (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

void
AES_CBC_MAC_Setkey(struct aes_cbc_mac_ctx *ctx, const uint8_t *key, uint16_t klen)
{
	ctx->rounds = rijndaelKeySetupEnc(ctx->keysched, key, klen * 8);
}
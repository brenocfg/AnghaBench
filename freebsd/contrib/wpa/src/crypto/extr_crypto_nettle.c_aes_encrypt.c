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
typedef  int /*<<< orphan*/  u8 ;
struct aes_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  nettle_aes_encrypt (struct aes_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int aes_encrypt(void *ctx, const u8 *plain, u8 *crypt)
{
	struct aes_ctx *actx = ctx;
	nettle_aes_encrypt(actx, AES_BLOCK_SIZE, crypt, plain);
	return 0;
}
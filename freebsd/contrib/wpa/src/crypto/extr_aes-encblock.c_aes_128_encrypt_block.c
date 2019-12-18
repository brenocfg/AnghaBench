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

/* Variables and functions */
 int /*<<< orphan*/  aes_encrypt (void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes_encrypt_deinit (void*) ; 
 void* aes_encrypt_init (int /*<<< orphan*/  const*,int) ; 

int aes_128_encrypt_block(const u8 *key, const u8 *in, u8 *out)
{
	void *ctx;
	ctx = aes_encrypt_init(key, 16);
	if (ctx == NULL)
		return -1;
	aes_encrypt(ctx, in, out);
	aes_encrypt_deinit(ctx);
	return 0;
}
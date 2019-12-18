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
typedef  int /*<<< orphan*/  u128 ;

/* Variables and functions */
 int /*<<< orphan*/  camellia_dec_blk_2way (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void camellia_decrypt_cbc_2way(void *ctx, u128 *dst, const u128 *src)
{
	u128 iv = *src;

	camellia_dec_blk_2way(ctx, (u8 *)dst, (u8 *)src);

	u128_xor(&dst[1], &dst[1], &iv);
}
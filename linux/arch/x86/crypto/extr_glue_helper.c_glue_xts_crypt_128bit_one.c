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
typedef  int /*<<< orphan*/  const u128 ;
typedef  int /*<<< orphan*/  le128 ;
typedef  int /*<<< orphan*/  (* common_glue_func_t ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  gf128mul_x_ble (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u128_xor (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

void glue_xts_crypt_128bit_one(void *ctx, u128 *dst, const u128 *src, le128 *iv,
			       common_glue_func_t fn)
{
	le128 ivblk = *iv;

	/* generate next IV */
	gf128mul_x_ble(iv, &ivblk);

	/* CC <- T xor C */
	u128_xor(dst, src, (u128 *)&ivblk);

	/* PP <- D(Key2,CC) */
	fn(ctx, (u8 *)dst, (u8 *)dst);

	/* P <- T xor PP */
	u128_xor(dst, dst, (u128 *)&ivblk);
}
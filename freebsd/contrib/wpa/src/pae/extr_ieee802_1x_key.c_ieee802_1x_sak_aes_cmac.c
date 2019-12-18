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
 int aes_kdf (int /*<<< orphan*/  const*,size_t,char*,int /*<<< orphan*/  const*,size_t,size_t,int /*<<< orphan*/ *) ; 

int ieee802_1x_sak_aes_cmac(const u8 *cak, size_t cak_bytes, const u8 *ctx,
			    size_t ctx_bytes, u8 *sak, size_t sak_bytes)
{
	return aes_kdf(cak, cak_bytes * 8, "IEEE8021 SAK", ctx, ctx_bytes * 8,
		       sak_bytes * 8, sak);
}
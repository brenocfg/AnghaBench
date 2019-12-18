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
typedef  int /*<<< orphan*/  context ;

/* Variables and functions */
 int ETH_ALEN ; 
 int aes_kdf (int /*<<< orphan*/  const*,int,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  joint_two_mac (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int ieee802_1x_cak_aes_cmac(const u8 *msk, size_t msk_bytes, const u8 *mac1,
			    const u8 *mac2, u8 *cak, size_t cak_bytes)
{
	u8 context[2 * ETH_ALEN];

	joint_two_mac(mac1, mac2, context);
	return aes_kdf(msk, 8 * msk_bytes, "IEEE8021 EAP CAK",
		       context, sizeof(context) * 8, 8 * cak_bytes, cak);
}
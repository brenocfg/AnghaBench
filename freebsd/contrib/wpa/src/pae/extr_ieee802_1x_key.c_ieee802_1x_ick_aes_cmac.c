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
 int aes_kdf (int /*<<< orphan*/  const*,int,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int ieee802_1x_ick_aes_cmac(const u8 *cak, size_t cak_bytes, const u8 *ckn,
			    size_t ckn_bytes, u8 *ick, size_t ick_bytes)
{
	u8 context[16];

	/* First 16 octets of CKN, with null octets appended to pad if needed */
	os_memset(context, 0, sizeof(context));
	os_memcpy(context, ckn, (ckn_bytes < 16) ? ckn_bytes : 16);

	return aes_kdf(cak, 8 *cak_bytes, "IEEE8021 ICK",
		       context, sizeof(context) * 8,
		       8 * ick_bytes, ick);
}
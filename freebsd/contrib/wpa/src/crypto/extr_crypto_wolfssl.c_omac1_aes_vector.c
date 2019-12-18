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
typedef  scalar_t__ word32 ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  Cmac ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 scalar_t__ TEST_FAIL () ; 
 int /*<<< orphan*/  WC_CMAC_AES ; 
 scalar_t__ wc_CmacFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ wc_CmacUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t const) ; 
 scalar_t__ wc_InitCmac (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int omac1_aes_vector(const u8 *key, size_t key_len, size_t num_elem,
		     const u8 *addr[], const size_t *len, u8 *mac)
{
	Cmac cmac;
	size_t i;
	word32 sz;

	if (TEST_FAIL())
		return -1;

	if (wc_InitCmac(&cmac, key, key_len, WC_CMAC_AES, NULL) != 0)
		return -1;

	for (i = 0; i < num_elem; i++)
		if (wc_CmacUpdate(&cmac, addr[i], len[i]) != 0)
			return -1;

	sz = AES_BLOCK_SIZE;
	if (wc_CmacFinal(&cmac, mac, &sz) != 0 || sz != AES_BLOCK_SIZE)
		return -1;

	return 0;
}
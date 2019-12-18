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
typedef  int /*<<< orphan*/  Aes ;

/* Variables and functions */
 int /*<<< orphan*/  AES_DECRYPTION ; 
 scalar_t__ TEST_FAIL () ; 
 int wc_AesCbcDecrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int wc_AesSetKey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int aes_128_cbc_decrypt(const u8 *key, const u8 *iv, u8 *data, size_t data_len)
{
	Aes aes;
	int ret;

	if (TEST_FAIL())
		return -1;

	ret = wc_AesSetKey(&aes, key, 16, iv, AES_DECRYPTION);
	if (ret != 0)
		return -1;

	ret = wc_AesCbcDecrypt(&aes, data, data, data_len);
	if (ret != 0)
		return -1;
	return 0;
}
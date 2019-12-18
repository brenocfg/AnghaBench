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
typedef  int /*<<< orphan*/  actx ;
typedef  int /*<<< orphan*/  AES_KEY ;

/* Variables and functions */
 scalar_t__ AES_set_decrypt_key (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int AES_unwrap_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ *,int) ; 
 scalar_t__ TEST_FAIL () ; 

int aes_unwrap(const u8 *kek, size_t kek_len, int n, const u8 *cipher,
	       u8 *plain)
{
	AES_KEY actx;
	int res;

	if (TEST_FAIL())
		return -1;
	if (AES_set_decrypt_key(kek, kek_len << 3, &actx))
		return -1;
	res = AES_unwrap_key(&actx, NULL, plain, cipher, (n + 1) * 8);
	OPENSSL_cleanse(&actx, sizeof(actx));
	return res <= 0 ? -1 : 0;
}
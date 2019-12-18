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
 scalar_t__ TEST_FAIL () ; 
 int wc_AesKeyWrap (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int aes_wrap(const u8 *kek, size_t kek_len, int n, const u8 *plain, u8 *cipher)
{
	int ret;

	if (TEST_FAIL())
		return -1;

	ret = wc_AesKeyWrap(kek, kek_len, plain, n * 8, cipher, (n + 1) * 8,
			    NULL);
	return ret != (n + 1) * 8 ? -1 : 0;
}
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
 int sha256_prf_bits (int /*<<< orphan*/  const*,size_t,char const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t) ; 

int sha256_prf(const u8 *key, size_t key_len, const char *label,
		const u8 *data, size_t data_len, u8 *buf, size_t buf_len)
{
	return sha256_prf_bits(key, key_len, label, data, data_len, buf,
			       buf_len * 8);
}
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
 int hmac_sha256 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int hmac_sha384 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int hmac_sha512 (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dpp_hmac(size_t hash_len, const u8 *key, size_t key_len,
		    const u8 *data, size_t data_len, u8 *mac)
{
	if (hash_len == 32)
		return hmac_sha256(key, key_len, data, data_len, mac);
	if (hash_len == 48)
		return hmac_sha384(key, key_len, data, data_len, mac);
	if (hash_len == 64)
		return hmac_sha512(key, key_len, data, data_len, mac);
	return -1;
}
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
 int hmac_sha256_kdf (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int hmac_sha384_kdf (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int hmac_sha512_kdf (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_strlen (char const*) ; 

__attribute__((used)) static int dpp_hkdf_expand(size_t hash_len, const u8 *secret, size_t secret_len,
			   const char *label, u8 *out, size_t outlen)
{
	if (hash_len == 32)
		return hmac_sha256_kdf(secret, secret_len, NULL,
				       (const u8 *) label, os_strlen(label),
				       out, outlen);
	if (hash_len == 48)
		return hmac_sha384_kdf(secret, secret_len, NULL,
				       (const u8 *) label, os_strlen(label),
				       out, outlen);
	if (hash_len == 64)
		return hmac_sha512_kdf(secret, secret_len, NULL,
				       (const u8 *) label, os_strlen(label),
				       out, outlen);
	return -1;
}
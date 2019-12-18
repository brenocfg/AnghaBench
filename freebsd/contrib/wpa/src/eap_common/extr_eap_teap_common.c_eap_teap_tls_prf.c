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
 int tls_prf_sha256 (int /*<<< orphan*/  const*,size_t,char const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int eap_teap_tls_prf(const u8 *secret, size_t secret_len,
			    const char *label, const u8 *seed, size_t seed_len,
			    u8 *out, size_t outlen)
{
	/* TODO: TLS-PRF for TLSv1.3 */
	return tls_prf_sha256(secret, secret_len, label, seed, seed_len,
			      out, outlen);
}
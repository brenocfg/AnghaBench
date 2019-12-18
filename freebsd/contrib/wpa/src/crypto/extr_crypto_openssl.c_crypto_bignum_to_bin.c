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
struct crypto_bignum {int dummy; } ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2bin (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_bn2bin_padded (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*) ; 
 int BN_bn2binpad (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t) ; 
 int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 scalar_t__ TEST_FAIL () ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int crypto_bignum_to_bin(const struct crypto_bignum *a,
			 u8 *buf, size_t buflen, size_t padlen)
{
	int num_bytes, offset;

	if (TEST_FAIL())
		return -1;

	if (padlen > buflen)
		return -1;

	if (padlen) {
#ifdef OPENSSL_IS_BORINGSSL
		if (BN_bn2bin_padded(buf, padlen, (const BIGNUM *) a) == 0)
			return -1;
		return padlen;
#else /* OPENSSL_IS_BORINGSSL */
#if OPENSSL_VERSION_NUMBER >= 0x10100000L && !defined(LIBRESSL_VERSION_NUMBER)
		return BN_bn2binpad((const BIGNUM *) a, buf, padlen);
#endif
#endif
	}

	num_bytes = BN_num_bytes((const BIGNUM *) a);
	if ((size_t) num_bytes > buflen)
		return -1;
	if (padlen > (size_t) num_bytes)
		offset = padlen - num_bytes;
	else
		offset = 0;

	os_memset(buf, 0, offset);
	BN_bn2bin((const BIGNUM *) a, buf + offset);

	return num_bytes + offset;
}
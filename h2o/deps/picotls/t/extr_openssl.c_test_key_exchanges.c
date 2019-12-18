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

/* Variables and functions */
 int /*<<< orphan*/  ptls_minicrypto_secp256r1 ; 
 int /*<<< orphan*/  ptls_minicrypto_x25519 ; 
 int /*<<< orphan*/  ptls_openssl_secp256r1 ; 
 int /*<<< orphan*/  ptls_openssl_secp384r1 ; 
 int /*<<< orphan*/  ptls_openssl_secp521r1 ; 
 int /*<<< orphan*/  ptls_openssl_x25519 ; 
 int /*<<< orphan*/  test_key_exchange (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_key_exchanges(void)
{
    test_key_exchange(&ptls_openssl_secp256r1, &ptls_openssl_secp256r1);
    test_key_exchange(&ptls_openssl_secp256r1, &ptls_minicrypto_secp256r1);
    test_key_exchange(&ptls_minicrypto_secp256r1, &ptls_openssl_secp256r1);

#if PTLS_OPENSSL_HAVE_SECP384R1
    test_key_exchange(&ptls_openssl_secp384r1, &ptls_openssl_secp384r1);
#endif

#if PTLS_OPENSSL_HAVE_SECP521R1
    test_key_exchange(&ptls_openssl_secp521r1, &ptls_openssl_secp521r1);
#endif

#if PTLS_OPENSSL_HAVE_X25519
    test_key_exchange(&ptls_openssl_x25519, &ptls_openssl_x25519);
    test_key_exchange(&ptls_openssl_x25519, &ptls_minicrypto_x25519);
    test_key_exchange(&ptls_minicrypto_x25519, &ptls_openssl_x25519);
#endif
}
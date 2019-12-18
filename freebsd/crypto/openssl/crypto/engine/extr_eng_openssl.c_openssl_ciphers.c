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
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int NID_rc4 ; 
 int NID_rc4_40 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int test_cipher_nids (int const**) ; 
 int /*<<< orphan*/ * test_r4_40_cipher () ; 
 int /*<<< orphan*/ * test_r4_cipher () ; 

__attribute__((used)) static int openssl_ciphers(ENGINE *e, const EVP_CIPHER **cipher,
                           const int **nids, int nid)
{
    if (!cipher) {
        /* We are returning a list of supported nids */
        return test_cipher_nids(nids);
    }
    /* We are being asked for a specific cipher */
    if (nid == NID_rc4)
        *cipher = test_r4_cipher();
    else if (nid == NID_rc4_40)
        *cipher = test_r4_40_cipher();
    else {
# ifdef TEST_ENG_OPENSSL_RC4_OTHERS
        fprintf(stderr, "(TEST_ENG_OPENSSL_RC4) returning NULL for "
                "nid %d\n", nid);
# endif
        *cipher = NULL;
        return 0;
    }
    return 1;
}
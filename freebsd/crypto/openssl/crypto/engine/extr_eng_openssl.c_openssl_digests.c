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
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int NID_sha1 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int test_digest_nids (int const**) ; 
 int /*<<< orphan*/ * test_sha_md () ; 

__attribute__((used)) static int openssl_digests(ENGINE *e, const EVP_MD **digest,
                           const int **nids, int nid)
{
    if (!digest) {
        /* We are returning a list of supported nids */
        return test_digest_nids(nids);
    }
    /* We are being asked for a specific digest */
    if (nid == NID_sha1)
        *digest = test_sha_md();
    else {
# ifdef TEST_ENG_OPENSSL_SHA_OTHERS
        fprintf(stderr, "(TEST_ENG_OPENSSL_SHA) returning NULL for "
                "nid %d\n", nid);
# endif
        *digest = NULL;
        return 0;
    }
    return 1;
}
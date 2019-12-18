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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_md_data (int /*<<< orphan*/ *) ; 
 int SHA1_Final (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int test_sha1_final(EVP_MD_CTX *ctx, unsigned char *md)
{
# ifdef TEST_ENG_OPENSSL_SHA_P_FINAL
    fprintf(stderr, "(TEST_ENG_OPENSSL_SHA) test_sha1_final() called\n");
# endif
    return SHA1_Final(md, EVP_MD_CTX_md_data(ctx));
}
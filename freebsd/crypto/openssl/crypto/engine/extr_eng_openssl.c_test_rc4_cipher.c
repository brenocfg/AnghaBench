#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ks; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,size_t,unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_rc4_cipher(EVP_CIPHER_CTX *ctx, unsigned char *out,
                           const unsigned char *in, size_t inl)
{
# ifdef TEST_ENG_OPENSSL_RC4_P_CIPHER
    fprintf(stderr, "(TEST_ENG_OPENSSL_RC4) test_cipher() called\n");
# endif
    RC4(&test(ctx)->ks, inl, in, out);
    return 1;
}
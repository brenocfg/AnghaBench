#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  sigbuf_small ;
struct TYPE_5__ {char const* base; int /*<<< orphan*/  off; } ;
typedef  TYPE_1__ ptls_buffer_t ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_generate_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_set1_EC_KEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int /*<<< orphan*/  NID_X9_62_prime256v1 ; 
 scalar_t__ do_sign (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  ptls_buffer_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  ptls_buffer_init (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptls_iovec_init (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ verify_sign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_ecdsa_sign(void)
{
    EVP_PKEY *pkey;

    { /* create pkey */
        EC_KEY *eckey = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
        EC_KEY_generate_key(eckey);
        pkey = EVP_PKEY_new();
        EVP_PKEY_set1_EC_KEY(pkey, eckey);
        EC_KEY_free(eckey);
    }

    const char *message = "hello world";
    ptls_buffer_t sigbuf;
    uint8_t sigbuf_small[1024];

    ptls_buffer_init(&sigbuf, sigbuf_small, sizeof(sigbuf_small));
    ok(do_sign(pkey, &sigbuf, ptls_iovec_init(message, strlen(message)), EVP_sha256()) == 0);
    EVP_PKEY_up_ref(pkey);
    ok(verify_sign(pkey, ptls_iovec_init(message, strlen(message)), ptls_iovec_init(sigbuf.base, sigbuf.off)) == 0);

    ptls_buffer_dispose(&sigbuf);
    EVP_PKEY_free(pkey);
}
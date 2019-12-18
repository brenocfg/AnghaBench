#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  sigbuf_small ;
struct TYPE_7__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ ptls_openssl_sign_certificate_t ;
struct TYPE_8__ {void const* base; int /*<<< orphan*/  off; } ;
typedef  TYPE_2__ ptls_buffer_t ;
struct TYPE_9__ {scalar_t__ sign_certificate; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_up_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 TYPE_6__* ctx ; 
 scalar_t__ do_sign (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 
 int /*<<< orphan*/  ptls_buffer_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  ptls_buffer_init (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptls_iovec_init (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (void const*) ; 
 scalar_t__ verify_sign (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_rsa_sign(void)
{
    ptls_openssl_sign_certificate_t *sc = (ptls_openssl_sign_certificate_t *)ctx->sign_certificate;

    const void *message = "hello world";
    ptls_buffer_t sigbuf;
    uint8_t sigbuf_small[1024];

    ptls_buffer_init(&sigbuf, sigbuf_small, sizeof(sigbuf_small));
    ok(do_sign(sc->key, &sigbuf, ptls_iovec_init(message, strlen(message)), EVP_sha256()) == 0);
    EVP_PKEY_up_ref(sc->key);
    ok(verify_sign(sc->key, ptls_iovec_init(message, strlen(message)), ptls_iovec_init(sigbuf.base, sigbuf.off)) == 0);

    ptls_buffer_dispose(&sigbuf);
}
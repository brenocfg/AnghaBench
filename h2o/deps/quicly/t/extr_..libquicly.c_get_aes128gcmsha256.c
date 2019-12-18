#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* tls; } ;
typedef  TYPE_2__ quicly_context_t ;
struct TYPE_8__ {scalar_t__ id; } ;
typedef  TYPE_3__ ptls_cipher_suite_t ;
struct TYPE_6__ {TYPE_3__** cipher_suites; } ;

/* Variables and functions */
 scalar_t__ PTLS_CIPHER_SUITE_AES_128_GCM_SHA256 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ptls_cipher_suite_t *get_aes128gcmsha256(quicly_context_t *ctx)
{
    ptls_cipher_suite_t **cs;

    for (cs = ctx->tls->cipher_suites;; ++cs) {
        assert(cs != NULL);
        if ((*cs)->id == PTLS_CIPHER_SUITE_AES_128_GCM_SHA256)
            break;
    }
    return *cs;
}
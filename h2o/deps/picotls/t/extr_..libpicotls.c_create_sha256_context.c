#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptls_hash_context_t ;
struct TYPE_6__ {TYPE_3__** cipher_suites; } ;
typedef  TYPE_2__ ptls_context_t ;
struct TYPE_7__ {int id; TYPE_1__* hash; } ;
typedef  TYPE_3__ ptls_cipher_suite_t ;
struct TYPE_5__ {int /*<<< orphan*/ * (* create ) () ;} ;

/* Variables and functions */
#define  PTLS_CIPHER_SUITE_AES_128_GCM_SHA256 129 
#define  PTLS_CIPHER_SUITE_CHACHA20_POLY1305_SHA256 128 
 int /*<<< orphan*/ * stub1 () ; 

__attribute__((used)) static ptls_hash_context_t *create_sha256_context(ptls_context_t *ctx)
{
    ptls_cipher_suite_t **cs;

    for (cs = ctx->cipher_suites; *cs != NULL; ++cs) {
        switch ((*cs)->id) {
        case PTLS_CIPHER_SUITE_AES_128_GCM_SHA256:
        case PTLS_CIPHER_SUITE_CHACHA20_POLY1305_SHA256:
            return (*cs)->hash->create();
        }
    }

    return NULL;
}
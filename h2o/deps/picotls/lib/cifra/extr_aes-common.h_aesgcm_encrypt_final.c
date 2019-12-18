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
struct aesgcm_context_t {int /*<<< orphan*/  gcm; } ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;

/* Variables and functions */
 size_t PTLS_AESGCM_TAG_SIZE ; 
 int /*<<< orphan*/  cf_gcm_encrypt_final (int /*<<< orphan*/ *,void*,size_t) ; 

__attribute__((used)) static inline size_t aesgcm_encrypt_final(ptls_aead_context_t *_ctx, void *output)
{
    struct aesgcm_context_t *ctx = (struct aesgcm_context_t *)_ctx;

    cf_gcm_encrypt_final(&ctx->gcm, output, PTLS_AESGCM_TAG_SIZE);
    return PTLS_AESGCM_TAG_SIZE;
}
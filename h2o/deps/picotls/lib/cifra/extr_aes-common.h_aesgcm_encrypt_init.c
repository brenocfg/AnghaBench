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
struct aesgcm_context_t {int /*<<< orphan*/  gcm; int /*<<< orphan*/  aes; } ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_AESGCM_IV_SIZE ; 
 int /*<<< orphan*/  cf_aes ; 
 int /*<<< orphan*/  cf_gcm_encrypt_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,size_t,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void aesgcm_encrypt_init(ptls_aead_context_t *_ctx, const void *iv, const void *aad, size_t aadlen)
{
    struct aesgcm_context_t *ctx = (struct aesgcm_context_t *)_ctx;

    cf_gcm_encrypt_init(&cf_aes, &ctx->aes, &ctx->gcm, aad, aadlen, iv, PTLS_AESGCM_IV_SIZE);
}
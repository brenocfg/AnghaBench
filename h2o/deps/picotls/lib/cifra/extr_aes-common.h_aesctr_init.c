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
struct aesctr_context_t {int /*<<< orphan*/  aes; int /*<<< orphan*/  ctr; } ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  cf_aes ; 
 int /*<<< orphan*/  cf_ctr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*) ; 

__attribute__((used)) static inline void aesctr_init(ptls_cipher_context_t *_ctx, const void *iv)
{
    struct aesctr_context_t *ctx = (struct aesctr_context_t *)_ctx;
    cf_ctr_init(&ctx->ctr, &cf_aes, &ctx->aes, iv);
}
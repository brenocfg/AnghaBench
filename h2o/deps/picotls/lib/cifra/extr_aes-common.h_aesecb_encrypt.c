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
struct aesecb_context_t {int /*<<< orphan*/  aes; } ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;

/* Variables and functions */
 size_t AES_BLOCKSZ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cf_aes_encrypt (int /*<<< orphan*/ *,void const*,void*) ; 

__attribute__((used)) static inline void aesecb_encrypt(ptls_cipher_context_t *_ctx, void *output, const void *input, size_t len)
{
    struct aesecb_context_t *ctx = (struct aesecb_context_t *)_ctx;
    assert(len % AES_BLOCKSZ == 0);
    cf_aes_encrypt(&ctx->aes, input, output);
}
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
struct cipher_context_t {int /*<<< orphan*/  evp; } ;
typedef  int /*<<< orphan*/  ptls_cipher_context_t ;

/* Variables and functions */
 int EVP_EncryptUpdate (int /*<<< orphan*/ ,void*,int*,void const*,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void cipher_encrypt(ptls_cipher_context_t *_ctx, void *output, const void *input, size_t _len)
{
    struct cipher_context_t *ctx = (struct cipher_context_t *)_ctx;
    int len = (int)_len, ret = EVP_EncryptUpdate(ctx->evp, output, &len, input, len);
    assert(ret);
    assert(len == (int)_len);
}
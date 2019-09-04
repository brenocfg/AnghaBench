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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;

/* Variables and functions */
 scalar_t__ ptls_aead_encrypt_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_aead_encrypt_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,size_t) ; 
 scalar_t__ ptls_aead_encrypt_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,size_t) ; 

size_t ptls_aead_encrypt(ptls_aead_context_t *ctx, void *output, const void *input, size_t inlen, uint64_t seq, const void *aad,
                         size_t aadlen)
{
    size_t off = 0;

    ptls_aead_encrypt_init(ctx, seq, aad, aadlen);
    off += ptls_aead_encrypt_update(ctx, ((uint8_t *)output) + off, input, inlen);
    off += ptls_aead_encrypt_final(ctx, ((uint8_t *)output) + off);

    return off;
}
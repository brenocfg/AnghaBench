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
typedef  int /*<<< orphan*/  ptls_aead_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_AES128_KEY_SIZE ; 
 int aead_aesgcm_setup_crypto (int /*<<< orphan*/ *,int,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aead_aes128gcm_setup_crypto(ptls_aead_context_t *ctx, int is_enc, const void *key)
{
    return aead_aesgcm_setup_crypto(ctx, is_enc, key, PTLS_AES128_KEY_SIZE);
}
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
struct st_quicly_cipher_context_t {int /*<<< orphan*/  header_protection; int /*<<< orphan*/  aead; } ;

/* Variables and functions */
 int /*<<< orphan*/  ptls_aead_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_cipher_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispose_cipher(struct st_quicly_cipher_context_t *ctx)
{
    ptls_aead_free(ctx->aead);
    ptls_cipher_free(ctx->header_protection);
}
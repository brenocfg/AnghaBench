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
struct st_quicly_default_encrypt_cid_t {int /*<<< orphan*/  reset_token_ctx; int /*<<< orphan*/  cid_decrypt_ctx; int /*<<< orphan*/  cid_encrypt_ctx; } ;
typedef  int /*<<< orphan*/  quicly_cid_encryptor_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct st_quicly_default_encrypt_cid_t*) ; 
 int /*<<< orphan*/  ptls_cipher_free (int /*<<< orphan*/ ) ; 

void quicly_free_default_cid_encryptor(quicly_cid_encryptor_t *_self)
{
    struct st_quicly_default_encrypt_cid_t *self = (void *)_self;

    ptls_cipher_free(self->cid_encrypt_ctx);
    ptls_cipher_free(self->cid_decrypt_ctx);
    ptls_cipher_free(self->reset_token_ctx);
    free(self);
}
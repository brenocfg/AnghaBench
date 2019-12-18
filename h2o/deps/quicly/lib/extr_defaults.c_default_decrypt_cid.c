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
typedef  int /*<<< orphan*/  const uint8_t ;
struct st_quicly_default_encrypt_cid_t {TYPE_3__* cid_decrypt_ctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  path_id; int /*<<< orphan*/  thread_id; int /*<<< orphan*/  master_id; int /*<<< orphan*/  node_id; } ;
typedef  TYPE_2__ quicly_cid_plaintext_t ;
typedef  int /*<<< orphan*/  quicly_cid_encryptor_t ;
struct TYPE_7__ {TYPE_1__* algo; } ;
struct TYPE_5__ {size_t block_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ptls_cipher_encrypt (TYPE_3__*,int /*<<< orphan*/  const*,void const*,size_t) ; 
 int /*<<< orphan*/  quicly_decode24 (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  quicly_decode32 (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  quicly_decode64 (int /*<<< orphan*/  const**) ; 

__attribute__((used)) static size_t default_decrypt_cid(quicly_cid_encryptor_t *_self, quicly_cid_plaintext_t *plaintext, const void *encrypted,
                                  size_t len)
{
    struct st_quicly_default_encrypt_cid_t *self = (void *)_self;
    uint8_t ptbuf[16], tmpbuf[16];
    const uint8_t *p;
    size_t cid_len;

    cid_len = self->cid_decrypt_ctx->algo->block_size;

    /* normalize the input, so that we would get consistent routing */
    if (len != 0 && len != cid_len) {
        if (len > cid_len)
            len = cid_len;
        memcpy(tmpbuf, encrypted, cid_len);
        if (len < cid_len)
            memset(tmpbuf + len, 0, cid_len - len);
        encrypted = tmpbuf;
    }

    /* decrypt */
    ptls_cipher_encrypt(self->cid_decrypt_ctx, ptbuf, encrypted, cid_len);

    /* decode */
    p = ptbuf;
    if (cid_len == 16) {
        plaintext->node_id = quicly_decode64(&p);
    } else {
        plaintext->node_id = 0;
    }
    plaintext->master_id = quicly_decode32(&p);
    plaintext->thread_id = quicly_decode24(&p);
    plaintext->path_id = *p++;
    assert(p - ptbuf == cid_len);

    return cid_len;
}
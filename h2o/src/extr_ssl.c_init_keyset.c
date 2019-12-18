#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/ * dec; int /*<<< orphan*/ * enc; } ;
struct st_quic_keyset_t {TYPE_1__ address_token; int /*<<< orphan*/ * cid; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  master_digestbuf ;
typedef  int /*<<< orphan*/  keybuf ;
struct TYPE_12__ {int /*<<< orphan*/  key_size; } ;

/* Variables and functions */
 int PTLS_MAX_DIGEST_SIZE ; 
 int PTLS_MAX_SECRET_SIZE ; 
 int /*<<< orphan*/  PTLS_SHA256_DIGEST_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* ptls_aead_new (TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ptls_calc_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_clear_memory (int /*<<< orphan*/ *,int) ; 
 int ptls_hkdf_expand_label (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__,char*,TYPE_2__,char*) ; 
 TYPE_2__ ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_openssl_aes128ecb ; 
 TYPE_4__ ptls_openssl_aes128gcm ; 
 int /*<<< orphan*/  ptls_openssl_bfecb ; 
 int /*<<< orphan*/  ptls_openssl_sha256 ; 
 int /*<<< orphan*/ * quicly_new_default_cid_encryptor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__) ; 

__attribute__((used)) static void init_keyset(struct st_quic_keyset_t *keyset, uint8_t name, ptls_iovec_t master_secret)
{
    uint8_t master_digestbuf[PTLS_MAX_DIGEST_SIZE], keybuf[PTLS_MAX_SECRET_SIZE];
    int ret;

    if (master_secret.len > PTLS_SHA256_DIGEST_SIZE) {
        ptls_calc_hash(&ptls_openssl_sha256, master_digestbuf, master_secret.base, master_secret.len);
        master_secret = ptls_iovec_init(master_digestbuf, PTLS_SHA256_DIGEST_SIZE);
    }

    keyset->name = name;
    keyset->cid =
        quicly_new_default_cid_encryptor(&ptls_openssl_bfecb, &ptls_openssl_aes128ecb, &ptls_openssl_sha256, master_secret);
    assert(keyset->cid != NULL);
    ret = ptls_hkdf_expand_label(&ptls_openssl_sha256, keybuf, ptls_openssl_aes128gcm.key_size, master_secret, "address-token",
                                 ptls_iovec_init(NULL, 0), "");
    assert(ret == 0);
    keyset->address_token.enc = ptls_aead_new(&ptls_openssl_aes128gcm, &ptls_openssl_sha256, 1, keybuf, "");
    assert(keyset->address_token.enc != NULL);
    keyset->address_token.dec = ptls_aead_new(&ptls_openssl_aes128gcm, &ptls_openssl_sha256, 0, keybuf, "");
    assert(keyset->address_token.dec != NULL);

    ptls_clear_memory(master_digestbuf, sizeof(master_digestbuf));
    ptls_clear_memory(keybuf, sizeof(keybuf));
}
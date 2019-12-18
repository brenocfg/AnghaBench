#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_9__ ;
typedef  struct TYPE_37__   TYPE_8__ ;
typedef  struct TYPE_36__   TYPE_7__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_23__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_18__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_37__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_35__ {int len; int /*<<< orphan*/  base; } ;
struct TYPE_36__ {TYPE_6__ encrypted_sni; TYPE_18__* cipher; int /*<<< orphan*/  peer_key; TYPE_4__* key_share; int /*<<< orphan*/  record_digest; } ;
struct st_ptls_client_hello_t {TYPE_8__ key_shares; TYPE_7__ esni; int /*<<< orphan*/  random_bytes; } ;
struct TYPE_38__ {int (* on_exchange ) (TYPE_9__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;TYPE_3__* algo; } ;
typedef  TYPE_9__ ptls_key_exchange_context_t ;
struct TYPE_24__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_10__ ptls_iovec_t ;
struct TYPE_25__ {int /*<<< orphan*/  nonce; int /*<<< orphan*/  esni_contents_hash; int /*<<< orphan*/  secret; int /*<<< orphan*/  version; } ;
typedef  TYPE_11__ ptls_esni_secret_t ;
struct TYPE_26__ {int padded_length; TYPE_9__** key_exchanges; int /*<<< orphan*/  version; TYPE_2__* cipher_suites; } ;
typedef  TYPE_12__ ptls_esni_context_t ;
struct TYPE_27__ {TYPE_12__** esni; } ;
typedef  TYPE_13__ ptls_context_t ;
typedef  int /*<<< orphan*/  ptls_aead_context_t ;
struct TYPE_34__ {int tag_size; } ;
struct TYPE_33__ {scalar_t__ id; } ;
struct TYPE_32__ {scalar_t__ id; } ;
struct TYPE_31__ {int /*<<< orphan*/  record_digest; TYPE_1__* cipher_suite; } ;
struct TYPE_30__ {int /*<<< orphan*/  digest_size; } ;
struct TYPE_29__ {scalar_t__ id; } ;
struct TYPE_28__ {scalar_t__ id; TYPE_5__* aead; TYPE_23__* hash; } ;

/* Variables and functions */
 int PTLS_ALERT_DECRYPT_ERROR ; 
 int PTLS_ALERT_ILLEGAL_PARAMETER ; 
 int PTLS_ERROR_NO_MEMORY ; 
 int PTLS_ESNI_NONCE_SIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int build_esni_contents_hash (TYPE_23__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int client_hello_decode_server_name (TYPE_10__*,char const**,char const* const) ; 
 int create_esni_aead (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_18__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_esni_secret (TYPE_11__**,int) ; 
 void* malloc (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memmove (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 int ptls_aead_decrypt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptls_aead_free (int /*<<< orphan*/ *) ; 
 TYPE_10__ ptls_iovec_init (char*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_9__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int client_hello_decrypt_esni(ptls_context_t *ctx, ptls_iovec_t *server_name, ptls_esni_secret_t **secret,
                                     struct st_ptls_client_hello_t *ch)
{
    ptls_esni_context_t **esni;
    ptls_key_exchange_context_t **key_share_ctx;
    uint8_t *decrypted = NULL;
    ptls_aead_context_t *aead = NULL;
    int ret;

    /* allocate secret */
    assert(*secret == NULL);
    if ((*secret = malloc(sizeof(**secret))) == NULL)
        return PTLS_ERROR_NO_MEMORY;
    memset(*secret, 0, sizeof(**secret));

    /* find the matching esni structure */
    for (esni = ctx->esni; *esni != NULL; ++esni) {
        size_t i;
        for (i = 0; (*esni)->cipher_suites[i].cipher_suite != NULL; ++i)
            if ((*esni)->cipher_suites[i].cipher_suite->id == ch->esni.cipher->id)
                break;
        if ((*esni)->cipher_suites[i].cipher_suite == NULL) {
            ret = PTLS_ALERT_ILLEGAL_PARAMETER;
            goto Exit;
        }
        if (memcmp((*esni)->cipher_suites[i].record_digest, ch->esni.record_digest, ch->esni.cipher->hash->digest_size) == 0) {
            (*secret)->version = (*esni)->version;
            break;
        }
    }
    if (*esni == NULL) {
        ret = PTLS_ALERT_ILLEGAL_PARAMETER;
        goto Exit;
    }

    /* find the matching private key for ESNI decryption */
    for (key_share_ctx = (*esni)->key_exchanges; *key_share_ctx != NULL; ++key_share_ctx)
        if ((*key_share_ctx)->algo->id == ch->esni.key_share->id)
            break;
    if (*key_share_ctx == NULL) {
        ret = PTLS_ALERT_ILLEGAL_PARAMETER;
        goto Exit;
    }

    /* calculate ESNIContents */
    if ((ret = build_esni_contents_hash(ch->esni.cipher->hash, (*secret)->esni_contents_hash, ch->esni.record_digest,
                                        ch->esni.key_share->id, ch->esni.peer_key, ch->random_bytes)) != 0)
        goto Exit;
    /* derive the shared secret */
    if ((ret = (*key_share_ctx)->on_exchange(key_share_ctx, 0, &(*secret)->secret, ch->esni.peer_key)) != 0)
        goto Exit;
    /* decrypt */
    if (ch->esni.encrypted_sni.len - ch->esni.cipher->aead->tag_size != (*esni)->padded_length + PTLS_ESNI_NONCE_SIZE) {
        ret = PTLS_ALERT_ILLEGAL_PARAMETER;
        goto Exit;
    }
    if ((decrypted = malloc((*esni)->padded_length + PTLS_ESNI_NONCE_SIZE)) == NULL) {
        ret = PTLS_ERROR_NO_MEMORY;
        goto Exit;
    }
    if ((ret = create_esni_aead(&aead, 0, ch->esni.cipher, (*secret)->secret, (*secret)->esni_contents_hash)) != 0)
        goto Exit;
    if (ptls_aead_decrypt(aead, decrypted, ch->esni.encrypted_sni.base, ch->esni.encrypted_sni.len, 0, ch->key_shares.base,
                          ch->key_shares.len) != (*esni)->padded_length + PTLS_ESNI_NONCE_SIZE) {
        ret = PTLS_ALERT_DECRYPT_ERROR;
        goto Exit;
    }
    ptls_aead_free(aead);
    aead = NULL;

    { /* decode sni */
        const uint8_t *src = decrypted, *const end = src + (*esni)->padded_length;
        ptls_iovec_t found_name;
        if (end - src < PTLS_ESNI_NONCE_SIZE) {
            ret = PTLS_ALERT_ILLEGAL_PARAMETER;
            goto Exit;
        }
        memcpy((*secret)->nonce, src, PTLS_ESNI_NONCE_SIZE);
        src += PTLS_ESNI_NONCE_SIZE;
        if ((ret = client_hello_decode_server_name(&found_name, &src, end)) != 0)
            goto Exit;
        for (; src != end; ++src) {
            if (*src != '\0') {
                ret = PTLS_ALERT_ILLEGAL_PARAMETER;
                goto Exit;
            }
        }
        /* if successful, reuse memory allocated for padded_server_name for storing the found name (freed by the caller) */
        memmove(decrypted, found_name.base, found_name.len);
        *server_name = ptls_iovec_init(decrypted, found_name.len);
        decrypted = NULL;
    }

    ret = 0;
Exit:
    if (decrypted != NULL)
        free(decrypted);
    if (aead != NULL)
        ptls_aead_free(aead);
    if (ret != 0 && *secret != NULL)
        free_esni_secret(secret, 1);
    return ret;
}
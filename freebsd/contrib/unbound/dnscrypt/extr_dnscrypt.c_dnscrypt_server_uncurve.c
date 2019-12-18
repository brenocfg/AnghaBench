#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sldns_buffer {int dummy; } ;
struct lruhash_entry {int /*<<< orphan*/  lock; int /*<<< orphan*/ * data; } ;
struct dnscrypt_query_header {int /*<<< orphan*/ * nonce; int /*<<< orphan*/  publickey; } ;
struct dnsc_env {int /*<<< orphan*/  shared_secrets_cache; int /*<<< orphan*/  shared_secrets_cache_lock; int /*<<< orphan*/  num_query_dnscrypt_secret_missed_cache; int /*<<< orphan*/  nonces_cache_lock; int /*<<< orphan*/  nonces_cache; int /*<<< orphan*/  num_query_dnscrypt_replay; } ;
struct TYPE_5__ {int* es_version; TYPE_1__* keypair; int /*<<< orphan*/  magic_query; } ;
typedef  TYPE_2__ dnsccert ;
struct TYPE_4__ {int /*<<< orphan*/  crypt_secretkey; } ;

/* Variables and functions */
 int DNSCRYPT_QUERY_BOX_OFFSET ; 
 size_t DNSCRYPT_QUERY_HEADER_SIZE ; 
 int DNSCRYPT_SHARED_SECRET_KEY_LENGTH ; 
 int crypto_box_BEFORENMBYTES ; 
 int crypto_box_HALF_NONCEBYTES ; 
 int crypto_box_NONCEBYTES ; 
 scalar_t__ crypto_box_beforenm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_beforenm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_box_curve25519xchacha20poly1305_open_easy_afternm (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_box_open_easy_afternm (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dnsc_nonce_cache_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnsc_nonce_cache_key_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lruhash_entry* dnsc_nonces_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnsc_shared_secret_cache_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dnsc_shared_secrets_cache_key (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lruhash_entry* dnsc_shared_secrets_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int* sldns_buffer_at (struct sldns_buffer*,size_t) ; 
 int /*<<< orphan*/ * sldns_buffer_begin (struct sldns_buffer*) ; 
 size_t sldns_buffer_limit (struct sldns_buffer*) ; 
 int /*<<< orphan*/  sldns_buffer_set_limit (struct sldns_buffer*,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_set_position (struct sldns_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dnscrypt_server_uncurve(struct dnsc_env* env,
                        const dnsccert *cert,
                        uint8_t client_nonce[crypto_box_HALF_NONCEBYTES],
                        uint8_t nmkey[crypto_box_BEFORENMBYTES],
                        struct sldns_buffer* buffer)
{
    size_t len = sldns_buffer_limit(buffer);
    uint8_t *const buf = sldns_buffer_begin(buffer);
    uint8_t nonce[crypto_box_NONCEBYTES];
    struct dnscrypt_query_header *query_header;
    // shared secret cache
    uint8_t key[DNSCRYPT_SHARED_SECRET_KEY_LENGTH];
    struct lruhash_entry* entry;
    uint32_t hash;

    uint32_t nonce_hash;

    if (len <= DNSCRYPT_QUERY_HEADER_SIZE) {
        return -1;
    }

    query_header = (struct dnscrypt_query_header *)buf;

    /* Detect replay attacks */
    nonce_hash = dnsc_nonce_cache_key_hash(
        query_header->nonce,
        cert->magic_query,
        query_header->publickey);

    lock_basic_lock(&env->nonces_cache_lock);
    entry = dnsc_nonces_lookup(
        env->nonces_cache,
        query_header->nonce,
        cert->magic_query,
        query_header->publickey,
        nonce_hash);

    if(entry) {
        lock_rw_unlock(&entry->lock);
        env->num_query_dnscrypt_replay++;
        lock_basic_unlock(&env->nonces_cache_lock);
        return -1;
    }

    dnsc_nonce_cache_insert(
        env->nonces_cache,
        query_header->nonce,
        cert->magic_query,
        query_header->publickey,
        nonce_hash);
    lock_basic_unlock(&env->nonces_cache_lock);

    /* Find existing shared secret */
    hash = dnsc_shared_secrets_cache_key(key,
                                         cert->es_version[1],
                                         query_header->publickey,
                                         cert->keypair->crypt_secretkey);
    entry = dnsc_shared_secrets_lookup(env->shared_secrets_cache,
                                       key,
                                       hash);

    if(!entry) {
        lock_basic_lock(&env->shared_secrets_cache_lock);
        env->num_query_dnscrypt_secret_missed_cache++;
        lock_basic_unlock(&env->shared_secrets_cache_lock);
        if(cert->es_version[1] == 2) {
#ifdef USE_DNSCRYPT_XCHACHA20
            if (crypto_box_curve25519xchacha20poly1305_beforenm(
                        nmkey, query_header->publickey,
                        cert->keypair->crypt_secretkey) != 0) {
                return -1;
            }
#else
            return -1;
#endif
    } else {
        if (crypto_box_beforenm(nmkey,
                                query_header->publickey,
                                cert->keypair->crypt_secretkey) != 0) {
            return -1;
        }
    }
    // Cache the shared secret we just computed.
    dnsc_shared_secret_cache_insert(env->shared_secrets_cache,
                                    key,
                                    hash,
                                    nmkey);
    } else {
        /* copy shared secret and unlock entry */
        memcpy(nmkey, entry->data, crypto_box_BEFORENMBYTES);
        lock_rw_unlock(&entry->lock);
    }

    memcpy(nonce, query_header->nonce, crypto_box_HALF_NONCEBYTES);
    memset(nonce + crypto_box_HALF_NONCEBYTES, 0, crypto_box_HALF_NONCEBYTES);

    if(cert->es_version[1] == 2) {
#ifdef USE_DNSCRYPT_XCHACHA20
        if (crypto_box_curve25519xchacha20poly1305_open_easy_afternm
                (buf,
                buf + DNSCRYPT_QUERY_BOX_OFFSET,
                len - DNSCRYPT_QUERY_BOX_OFFSET, nonce,
                nmkey) != 0) {
            return -1;
        }
#else
        return -1;
#endif
    } else {
        if (crypto_box_open_easy_afternm
            (buf,
             buf + DNSCRYPT_QUERY_BOX_OFFSET,
             len - DNSCRYPT_QUERY_BOX_OFFSET, nonce,
             nmkey) != 0) {
            return -1;
        }
    }

    len -= DNSCRYPT_QUERY_HEADER_SIZE;

    while (*sldns_buffer_at(buffer, --len) == 0)
        ;

    if (*sldns_buffer_at(buffer, len) != 0x80) {
        return -1;
    }

    memcpy(client_nonce, nonce, crypto_box_HALF_NONCEBYTES);

    sldns_buffer_set_position(buffer, 0);
    sldns_buffer_set_limit(buffer, len);

    return 0;
}
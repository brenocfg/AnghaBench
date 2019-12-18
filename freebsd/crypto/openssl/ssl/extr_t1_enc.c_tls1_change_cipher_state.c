#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  enc_write_state; } ;
struct TYPE_12__ {scalar_t__ use_etm; } ;
struct TYPE_17__ {TYPE_1__ statem; TYPE_5__* s3; int /*<<< orphan*/  rlayer; int /*<<< orphan*/ * compress; int /*<<< orphan*/ * write_hash; int /*<<< orphan*/ * enc_write_ctx; int /*<<< orphan*/  mac_flags; TYPE_2__ ext; int /*<<< orphan*/ * expand; int /*<<< orphan*/ * read_hash; int /*<<< orphan*/ * enc_read_ctx; } ;
struct TYPE_16__ {int /*<<< orphan*/  method; } ;
struct TYPE_14__ {int new_mac_pkey_type; unsigned char* key_block; size_t new_mac_secret_size; size_t key_block_length; TYPE_3__* new_cipher; TYPE_6__* new_compression; int /*<<< orphan*/ * new_hash; int /*<<< orphan*/ * new_sym_enc; } ;
struct TYPE_15__ {unsigned char* read_mac_secret; size_t read_mac_secret_size; unsigned char* write_mac_secret; size_t write_mac_secret_size; TYPE_4__ tmp; int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {int algorithm2; int algorithm_enc; } ;
typedef  TYPE_6__ SSL_COMP ;
typedef  TYPE_7__ SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CTX_free (int /*<<< orphan*/ *) ; 
 void* COMP_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENC_WRITE_STATE_INVALID ; 
 int /*<<< orphan*/  ENC_WRITE_STATE_VALID ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int EVP_CCM8_TLS_TAG_LEN ; 
 size_t EVP_CCM_TLS_FIXED_IV_LEN ; 
 int EVP_CCM_TLS_TAG_LEN ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned char*) ; 
 void* EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_reset (int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_flags (int /*<<< orphan*/  const*) ; 
 size_t EVP_CIPHER_iv_length (int /*<<< orphan*/  const*) ; 
 int EVP_CIPHER_key_length (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_CIPHER_mode (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_CIPH_CCM_MODE ; 
 int EVP_CIPH_FLAG_AEAD_CIPHER ; 
 scalar_t__ EVP_CIPH_GCM_MODE ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_SET_IVLEN ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_SET_MAC_KEY ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_SET_TAG ; 
 int /*<<< orphan*/  EVP_CTRL_CCM_SET_IV_FIXED ; 
 int /*<<< orphan*/  EVP_CTRL_GCM_SET_IV_FIXED ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char*,unsigned char*,int) ; 
 scalar_t__ EVP_DigestSignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t EVP_GCM_TLS_FIXED_IV_LEN ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new_mac_key (int,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  RECORD_LAYER_reset_read_sequence (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RECORD_LAYER_reset_write_sequence (int /*<<< orphan*/ *) ; 
 int SSL3_CC_READ ; 
 int SSL3_CC_WRITE ; 
 int SSL3_CHANGE_CIPHER_CLIENT_WRITE ; 
 int SSL3_CHANGE_CIPHER_SERVER_READ ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int SSL_AES128CCM8 ; 
 int SSL_AES256CCM8 ; 
 int /*<<< orphan*/  SSL_F_TLS1_CHANGE_CIPHER_STATE ; 
 scalar_t__ SSL_IS_DTLS (TYPE_7__*) ; 
 int /*<<< orphan*/  SSL_MAC_FLAG_READ_MAC_STREAM ; 
 int /*<<< orphan*/  SSL_MAC_FLAG_WRITE_MAC_STREAM ; 
 int /*<<< orphan*/  SSL_R_COMPRESSION_LIBRARY_ERROR ; 
 int /*<<< orphan*/  SSLfatal (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_FLAGS_ENCRYPT_THEN_MAC_READ ; 
 int /*<<< orphan*/  TLS1_FLAGS_ENCRYPT_THEN_MAC_WRITE ; 
 int TLS1_STREAM_MAC ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * ssl_replace_hash (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int tls1_change_cipher_state(SSL *s, int which)
{
    unsigned char *p, *mac_secret;
    unsigned char *ms, *key, *iv;
    EVP_CIPHER_CTX *dd;
    const EVP_CIPHER *c;
#ifndef OPENSSL_NO_COMP
    const SSL_COMP *comp;
#endif
    const EVP_MD *m;
    int mac_type;
    size_t *mac_secret_size;
    EVP_MD_CTX *mac_ctx;
    EVP_PKEY *mac_key;
    size_t n, i, j, k, cl;
    int reuse_dd = 0;

    c = s->s3->tmp.new_sym_enc;
    m = s->s3->tmp.new_hash;
    mac_type = s->s3->tmp.new_mac_pkey_type;
#ifndef OPENSSL_NO_COMP
    comp = s->s3->tmp.new_compression;
#endif

    if (which & SSL3_CC_READ) {
        if (s->ext.use_etm)
            s->s3->flags |= TLS1_FLAGS_ENCRYPT_THEN_MAC_READ;
        else
            s->s3->flags &= ~TLS1_FLAGS_ENCRYPT_THEN_MAC_READ;

        if (s->s3->tmp.new_cipher->algorithm2 & TLS1_STREAM_MAC)
            s->mac_flags |= SSL_MAC_FLAG_READ_MAC_STREAM;
        else
            s->mac_flags &= ~SSL_MAC_FLAG_READ_MAC_STREAM;

        if (s->enc_read_ctx != NULL) {
            reuse_dd = 1;
        } else if ((s->enc_read_ctx = EVP_CIPHER_CTX_new()) == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS1_CHANGE_CIPHER_STATE,
                     ERR_R_MALLOC_FAILURE);
            goto err;
        } else {
            /*
             * make sure it's initialised in case we exit later with an error
             */
            EVP_CIPHER_CTX_reset(s->enc_read_ctx);
        }
        dd = s->enc_read_ctx;
        mac_ctx = ssl_replace_hash(&s->read_hash, NULL);
        if (mac_ctx == NULL)
            goto err;
#ifndef OPENSSL_NO_COMP
        COMP_CTX_free(s->expand);
        s->expand = NULL;
        if (comp != NULL) {
            s->expand = COMP_CTX_new(comp->method);
            if (s->expand == NULL) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS1_CHANGE_CIPHER_STATE,
                         SSL_R_COMPRESSION_LIBRARY_ERROR);
                goto err;
            }
        }
#endif
        /*
         * this is done by dtls1_reset_seq_numbers for DTLS
         */
        if (!SSL_IS_DTLS(s))
            RECORD_LAYER_reset_read_sequence(&s->rlayer);
        mac_secret = &(s->s3->read_mac_secret[0]);
        mac_secret_size = &(s->s3->read_mac_secret_size);
    } else {
        s->statem.enc_write_state = ENC_WRITE_STATE_INVALID;
        if (s->ext.use_etm)
            s->s3->flags |= TLS1_FLAGS_ENCRYPT_THEN_MAC_WRITE;
        else
            s->s3->flags &= ~TLS1_FLAGS_ENCRYPT_THEN_MAC_WRITE;

        if (s->s3->tmp.new_cipher->algorithm2 & TLS1_STREAM_MAC)
            s->mac_flags |= SSL_MAC_FLAG_WRITE_MAC_STREAM;
        else
            s->mac_flags &= ~SSL_MAC_FLAG_WRITE_MAC_STREAM;
        if (s->enc_write_ctx != NULL && !SSL_IS_DTLS(s)) {
            reuse_dd = 1;
        } else if ((s->enc_write_ctx = EVP_CIPHER_CTX_new()) == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS1_CHANGE_CIPHER_STATE,
                     ERR_R_MALLOC_FAILURE);
            goto err;
        }
        dd = s->enc_write_ctx;
        if (SSL_IS_DTLS(s)) {
            mac_ctx = EVP_MD_CTX_new();
            if (mac_ctx == NULL) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS1_CHANGE_CIPHER_STATE,
                         ERR_R_MALLOC_FAILURE);
                goto err;
            }
            s->write_hash = mac_ctx;
        } else {
            mac_ctx = ssl_replace_hash(&s->write_hash, NULL);
            if (mac_ctx == NULL) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS1_CHANGE_CIPHER_STATE,
                         ERR_R_MALLOC_FAILURE);
                goto err;
            }
        }
#ifndef OPENSSL_NO_COMP
        COMP_CTX_free(s->compress);
        s->compress = NULL;
        if (comp != NULL) {
            s->compress = COMP_CTX_new(comp->method);
            if (s->compress == NULL) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS1_CHANGE_CIPHER_STATE,
                        SSL_R_COMPRESSION_LIBRARY_ERROR);
                goto err;
            }
        }
#endif
        /*
         * this is done by dtls1_reset_seq_numbers for DTLS
         */
        if (!SSL_IS_DTLS(s))
            RECORD_LAYER_reset_write_sequence(&s->rlayer);
        mac_secret = &(s->s3->write_mac_secret[0]);
        mac_secret_size = &(s->s3->write_mac_secret_size);
    }

    if (reuse_dd)
        EVP_CIPHER_CTX_reset(dd);

    p = s->s3->tmp.key_block;
    i = *mac_secret_size = s->s3->tmp.new_mac_secret_size;

    /* TODO(size_t): convert me */
    cl = EVP_CIPHER_key_length(c);
    j = cl;
    /* Was j=(exp)?5:EVP_CIPHER_key_length(c); */
    /* If GCM/CCM mode only part of IV comes from PRF */
    if (EVP_CIPHER_mode(c) == EVP_CIPH_GCM_MODE)
        k = EVP_GCM_TLS_FIXED_IV_LEN;
    else if (EVP_CIPHER_mode(c) == EVP_CIPH_CCM_MODE)
        k = EVP_CCM_TLS_FIXED_IV_LEN;
    else
        k = EVP_CIPHER_iv_length(c);
    if ((which == SSL3_CHANGE_CIPHER_CLIENT_WRITE) ||
        (which == SSL3_CHANGE_CIPHER_SERVER_READ)) {
        ms = &(p[0]);
        n = i + i;
        key = &(p[n]);
        n += j + j;
        iv = &(p[n]);
        n += k + k;
    } else {
        n = i;
        ms = &(p[n]);
        n += i + j;
        key = &(p[n]);
        n += j + k;
        iv = &(p[n]);
        n += k;
    }

    if (n > s->s3->tmp.key_block_length) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS1_CHANGE_CIPHER_STATE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    memcpy(mac_secret, ms, i);

    if (!(EVP_CIPHER_flags(c) & EVP_CIPH_FLAG_AEAD_CIPHER)) {
        /* TODO(size_t): Convert this function */
        mac_key = EVP_PKEY_new_mac_key(mac_type, NULL, mac_secret,
                                               (int)*mac_secret_size);
        if (mac_key == NULL
            || EVP_DigestSignInit(mac_ctx, NULL, m, NULL, mac_key) <= 0) {
            EVP_PKEY_free(mac_key);
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS1_CHANGE_CIPHER_STATE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
        EVP_PKEY_free(mac_key);
    }
#ifdef SSL_DEBUG
    printf("which = %04X\nmac key=", which);
    {
        size_t z;
        for (z = 0; z < i; z++)
            printf("%02X%c", ms[z], ((z + 1) % 16) ? ' ' : '\n');
    }
#endif

    if (EVP_CIPHER_mode(c) == EVP_CIPH_GCM_MODE) {
        if (!EVP_CipherInit_ex(dd, c, NULL, key, NULL, (which & SSL3_CC_WRITE))
            || !EVP_CIPHER_CTX_ctrl(dd, EVP_CTRL_GCM_SET_IV_FIXED, (int)k,
                                    iv)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS1_CHANGE_CIPHER_STATE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
    } else if (EVP_CIPHER_mode(c) == EVP_CIPH_CCM_MODE) {
        int taglen;
        if (s->s3->tmp.
            new_cipher->algorithm_enc & (SSL_AES128CCM8 | SSL_AES256CCM8))
            taglen = EVP_CCM8_TLS_TAG_LEN;
        else
            taglen = EVP_CCM_TLS_TAG_LEN;
        if (!EVP_CipherInit_ex(dd, c, NULL, NULL, NULL, (which & SSL3_CC_WRITE))
            || !EVP_CIPHER_CTX_ctrl(dd, EVP_CTRL_AEAD_SET_IVLEN, 12, NULL)
            || !EVP_CIPHER_CTX_ctrl(dd, EVP_CTRL_AEAD_SET_TAG, taglen, NULL)
            || !EVP_CIPHER_CTX_ctrl(dd, EVP_CTRL_CCM_SET_IV_FIXED, (int)k, iv)
            || !EVP_CipherInit_ex(dd, NULL, NULL, key, NULL, -1)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS1_CHANGE_CIPHER_STATE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
    } else {
        if (!EVP_CipherInit_ex(dd, c, NULL, key, iv, (which & SSL3_CC_WRITE))) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS1_CHANGE_CIPHER_STATE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
    }
    /* Needed for "composite" AEADs, such as RC4-HMAC-MD5 */
    if ((EVP_CIPHER_flags(c) & EVP_CIPH_FLAG_AEAD_CIPHER) && *mac_secret_size
        && !EVP_CIPHER_CTX_ctrl(dd, EVP_CTRL_AEAD_SET_MAC_KEY,
                                (int)*mac_secret_size, mac_secret)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS1_CHANGE_CIPHER_STATE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }
    s->statem.enc_write_state = ENC_WRITE_STATE_VALID;

#ifdef SSL_DEBUG
    printf("which = %04X\nkey=", which);
    {
        int z;
        for (z = 0; z < EVP_CIPHER_key_length(c); z++)
            printf("%02X%c", key[z], ((z + 1) % 16) ? ' ' : '\n');
    }
    printf("\niv=");
    {
        size_t z;
        for (z = 0; z < k; z++)
            printf("%02X%c", iv[z], ((z + 1) % 16) ? ' ' : '\n');
    }
    printf("\n");
#endif

    return 1;
 err:
    return 0;
}
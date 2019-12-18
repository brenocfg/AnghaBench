#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  enc_write_state; } ;
struct TYPE_12__ {TYPE_4__ statem; TYPE_3__* s3; int /*<<< orphan*/  rlayer; int /*<<< orphan*/ * compress; int /*<<< orphan*/  write_hash; int /*<<< orphan*/ * enc_write_ctx; int /*<<< orphan*/ * expand; int /*<<< orphan*/  read_hash; int /*<<< orphan*/ * enc_read_ctx; } ;
struct TYPE_9__ {unsigned char* key_block; size_t key_block_length; TYPE_1__* new_compression; int /*<<< orphan*/ * new_hash; int /*<<< orphan*/ * new_sym_enc; } ;
struct TYPE_10__ {unsigned char* read_mac_secret; unsigned char* write_mac_secret; TYPE_2__ tmp; } ;
struct TYPE_8__ {int /*<<< orphan*/ * method; } ;
typedef  TYPE_5__ SSL ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  COMP_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CTX_free (int /*<<< orphan*/ *) ; 
 void* COMP_CTX_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENC_WRITE_STATE_INVALID ; 
 int /*<<< orphan*/  ENC_WRITE_STATE_VALID ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 void* EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_reset (int /*<<< orphan*/ *) ; 
 size_t EVP_CIPHER_iv_length (int /*<<< orphan*/  const*) ; 
 size_t EVP_CIPHER_key_length (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char*,unsigned char*,int) ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RECORD_LAYER_reset_read_sequence (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RECORD_LAYER_reset_write_sequence (int /*<<< orphan*/ *) ; 
 int SSL3_CC_READ ; 
 int SSL3_CC_WRITE ; 
 int SSL3_CHANGE_CIPHER_CLIENT_WRITE ; 
 int SSL3_CHANGE_CIPHER_SERVER_READ ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL3_CHANGE_CIPHER_STATE ; 
 int /*<<< orphan*/  SSL_R_COMPRESSION_LIBRARY_ERROR ; 
 int /*<<< orphan*/  SSLfatal (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ssl_replace_hash (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int ssl3_change_cipher_state(SSL *s, int which)
{
    unsigned char *p, *mac_secret;
    unsigned char *ms, *key, *iv;
    EVP_CIPHER_CTX *dd;
    const EVP_CIPHER *c;
#ifndef OPENSSL_NO_COMP
    COMP_METHOD *comp;
#endif
    const EVP_MD *m;
    int mdi;
    size_t n, i, j, k, cl;
    int reuse_dd = 0;

    c = s->s3->tmp.new_sym_enc;
    m = s->s3->tmp.new_hash;
    /* m == NULL will lead to a crash later */
    if (!ossl_assert(m != NULL)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_CHANGE_CIPHER_STATE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }
#ifndef OPENSSL_NO_COMP
    if (s->s3->tmp.new_compression == NULL)
        comp = NULL;
    else
        comp = s->s3->tmp.new_compression->method;
#endif

    if (which & SSL3_CC_READ) {
        if (s->enc_read_ctx != NULL) {
            reuse_dd = 1;
        } else if ((s->enc_read_ctx = EVP_CIPHER_CTX_new()) == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_CHANGE_CIPHER_STATE,
                     ERR_R_MALLOC_FAILURE);
            goto err;
        } else {
            /*
             * make sure it's initialised in case we exit later with an error
             */
            EVP_CIPHER_CTX_reset(s->enc_read_ctx);
        }
        dd = s->enc_read_ctx;

        if (ssl_replace_hash(&s->read_hash, m) == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_CHANGE_CIPHER_STATE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
#ifndef OPENSSL_NO_COMP
        /* COMPRESS */
        COMP_CTX_free(s->expand);
        s->expand = NULL;
        if (comp != NULL) {
            s->expand = COMP_CTX_new(comp);
            if (s->expand == NULL) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_SSL3_CHANGE_CIPHER_STATE,
                         SSL_R_COMPRESSION_LIBRARY_ERROR);
                goto err;
            }
        }
#endif
        RECORD_LAYER_reset_read_sequence(&s->rlayer);
        mac_secret = &(s->s3->read_mac_secret[0]);
    } else {
        s->statem.enc_write_state = ENC_WRITE_STATE_INVALID;
        if (s->enc_write_ctx != NULL) {
            reuse_dd = 1;
        } else if ((s->enc_write_ctx = EVP_CIPHER_CTX_new()) == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_CHANGE_CIPHER_STATE,
                     ERR_R_MALLOC_FAILURE);
            goto err;
        } else {
            /*
             * make sure it's initialised in case we exit later with an error
             */
            EVP_CIPHER_CTX_reset(s->enc_write_ctx);
        }
        dd = s->enc_write_ctx;
        if (ssl_replace_hash(&s->write_hash, m) == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_CHANGE_CIPHER_STATE,
                     ERR_R_MALLOC_FAILURE);
            goto err;
        }
#ifndef OPENSSL_NO_COMP
        /* COMPRESS */
        COMP_CTX_free(s->compress);
        s->compress = NULL;
        if (comp != NULL) {
            s->compress = COMP_CTX_new(comp);
            if (s->compress == NULL) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_SSL3_CHANGE_CIPHER_STATE,
                         SSL_R_COMPRESSION_LIBRARY_ERROR);
                goto err;
            }
        }
#endif
        RECORD_LAYER_reset_write_sequence(&s->rlayer);
        mac_secret = &(s->s3->write_mac_secret[0]);
    }

    if (reuse_dd)
        EVP_CIPHER_CTX_reset(dd);

    p = s->s3->tmp.key_block;
    mdi = EVP_MD_size(m);
    if (mdi < 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_CHANGE_CIPHER_STATE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }
    i = mdi;
    cl = EVP_CIPHER_key_length(c);
    j = cl;
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
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_CHANGE_CIPHER_STATE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    memcpy(mac_secret, ms, i);

    if (!EVP_CipherInit_ex(dd, c, NULL, key, iv, (which & SSL3_CC_WRITE))) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_CHANGE_CIPHER_STATE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    s->statem.enc_write_state = ENC_WRITE_STATE_VALID;
    return 1;
 err:
    return 0;
}
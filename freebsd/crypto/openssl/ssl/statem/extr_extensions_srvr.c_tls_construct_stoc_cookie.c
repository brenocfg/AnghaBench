#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_19__ {TYPE_6__* session_ctx; TYPE_4__* ctx; TYPE_3__* s3; TYPE_1__* method; } ;
struct TYPE_17__ {int /*<<< orphan*/  cookie_hmac_key; } ;
struct TYPE_18__ {TYPE_5__ ext; } ;
struct TYPE_16__ {scalar_t__ (* gen_stateless_cookie_cb ) (TYPE_7__*,unsigned char*,size_t*) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  new_cipher; } ;
struct TYPE_15__ {int flags; int /*<<< orphan*/ * peer_tmp; TYPE_2__ tmp; int /*<<< orphan*/  group_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* put_cipher_by_char ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ;} ;
typedef  TYPE_7__ SSL ;
typedef  int EXT_RETURN ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  COOKIE_STATE_FORMAT_VERSION ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ EVP_DigestSign (int /*<<< orphan*/ *,unsigned char*,size_t*,unsigned char*,size_t) ; 
 scalar_t__ EVP_DigestSignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_HMAC ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new_raw_private_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int EXT_RETURN_FAIL ; 
 int EXT_RETURN_NOT_SENT ; 
 int EXT_RETURN_SENT ; 
 size_t MAX_COOKIE_SIZE ; 
 size_t SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 size_t SSL_COOKIE_LENGTH ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_STOC_COOKIE ; 
 int /*<<< orphan*/  SSL_R_COOKIE_GEN_CALLBACK_FAILURE ; 
 int /*<<< orphan*/  SSL_R_NO_COOKIE_CALLBACK_SET ; 
 int /*<<< orphan*/  SSLfatal (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_3_VERSION ; 
 int TLS1_FLAGS_STATELESS ; 
 int /*<<< orphan*/  TLSEXT_TYPE_cookie ; 
 int /*<<< orphan*/  WPACKET_allocate_bytes (int /*<<< orphan*/ *,size_t,unsigned char**) ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_get_total_written (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u32 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_reserve_bytes (int /*<<< orphan*/ *,size_t,unsigned char**) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  ssl3_digest_cached_records (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_handshake_hash (TYPE_7__*,unsigned char*,size_t,size_t*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ stub2 (TYPE_7__*,unsigned char*,size_t*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

EXT_RETURN tls_construct_stoc_cookie(SSL *s, WPACKET *pkt, unsigned int context,
                                     X509 *x, size_t chainidx)
{
#ifndef OPENSSL_NO_TLS1_3
    unsigned char *hashval1, *hashval2, *appcookie1, *appcookie2, *cookie;
    unsigned char *hmac, *hmac2;
    size_t startlen, ciphlen, totcookielen, hashlen, hmaclen, appcookielen;
    EVP_MD_CTX *hctx;
    EVP_PKEY *pkey;
    int ret = EXT_RETURN_FAIL;

    if ((s->s3->flags & TLS1_FLAGS_STATELESS) == 0)
        return EXT_RETURN_NOT_SENT;

    if (s->ctx->gen_stateless_cookie_cb == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_COOKIE,
                 SSL_R_NO_COOKIE_CALLBACK_SET);
        return EXT_RETURN_FAIL;
    }

    if (!WPACKET_put_bytes_u16(pkt, TLSEXT_TYPE_cookie)
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_get_total_written(pkt, &startlen)
            || !WPACKET_reserve_bytes(pkt, MAX_COOKIE_SIZE, &cookie)
            || !WPACKET_put_bytes_u16(pkt, COOKIE_STATE_FORMAT_VERSION)
            || !WPACKET_put_bytes_u16(pkt, TLS1_3_VERSION)
            || !WPACKET_put_bytes_u16(pkt, s->s3->group_id)
            || !s->method->put_cipher_by_char(s->s3->tmp.new_cipher, pkt,
                                              &ciphlen)
               /* Is there a key_share extension present in this HRR? */
            || !WPACKET_put_bytes_u8(pkt, s->s3->peer_tmp == NULL)
            || !WPACKET_put_bytes_u32(pkt, (unsigned int)time(NULL))
            || !WPACKET_start_sub_packet_u16(pkt)
            || !WPACKET_reserve_bytes(pkt, EVP_MAX_MD_SIZE, &hashval1)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_COOKIE,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    /*
     * Get the hash of the initial ClientHello. ssl_handshake_hash() operates
     * on raw buffers, so we first reserve sufficient bytes (above) and then
     * subsequently allocate them (below)
     */
    if (!ssl3_digest_cached_records(s, 0)
            || !ssl_handshake_hash(s, hashval1, EVP_MAX_MD_SIZE, &hashlen)) {
        /* SSLfatal() already called */
        return EXT_RETURN_FAIL;
    }

    if (!WPACKET_allocate_bytes(pkt, hashlen, &hashval2)
            || !ossl_assert(hashval1 == hashval2)
            || !WPACKET_close(pkt)
            || !WPACKET_start_sub_packet_u8(pkt)
            || !WPACKET_reserve_bytes(pkt, SSL_COOKIE_LENGTH, &appcookie1)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_COOKIE,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    /* Generate the application cookie */
    if (s->ctx->gen_stateless_cookie_cb(s, appcookie1, &appcookielen) == 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_COOKIE,
                 SSL_R_COOKIE_GEN_CALLBACK_FAILURE);
        return EXT_RETURN_FAIL;
    }

    if (!WPACKET_allocate_bytes(pkt, appcookielen, &appcookie2)
            || !ossl_assert(appcookie1 == appcookie2)
            || !WPACKET_close(pkt)
            || !WPACKET_get_total_written(pkt, &totcookielen)
            || !WPACKET_reserve_bytes(pkt, SHA256_DIGEST_LENGTH, &hmac)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_COOKIE,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }
    hmaclen = SHA256_DIGEST_LENGTH;

    totcookielen -= startlen;
    if (!ossl_assert(totcookielen <= MAX_COOKIE_SIZE - SHA256_DIGEST_LENGTH)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_COOKIE,
                 ERR_R_INTERNAL_ERROR);
        return EXT_RETURN_FAIL;
    }

    /* HMAC the cookie */
    hctx = EVP_MD_CTX_create();
    pkey = EVP_PKEY_new_raw_private_key(EVP_PKEY_HMAC, NULL,
                                        s->session_ctx->ext.cookie_hmac_key,
                                        sizeof(s->session_ctx->ext
                                               .cookie_hmac_key));
    if (hctx == NULL || pkey == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_COOKIE,
                 ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (EVP_DigestSignInit(hctx, NULL, EVP_sha256(), NULL, pkey) <= 0
            || EVP_DigestSign(hctx, hmac, &hmaclen, cookie,
                              totcookielen) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_COOKIE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    if (!ossl_assert(totcookielen + hmaclen <= MAX_COOKIE_SIZE)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_COOKIE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    if (!WPACKET_allocate_bytes(pkt, hmaclen, &hmac2)
            || !ossl_assert(hmac == hmac2)
            || !ossl_assert(cookie == hmac - totcookielen)
            || !WPACKET_close(pkt)
            || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_STOC_COOKIE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    ret = EXT_RETURN_SENT;

 err:
    EVP_MD_CTX_free(hctx);
    EVP_PKEY_free(pkey);
    return ret;
#else
    return EXT_RETURN_FAIL;
#endif
}
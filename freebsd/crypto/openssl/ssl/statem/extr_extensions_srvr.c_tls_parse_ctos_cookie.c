#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hrr ;
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_15__ {int cookieok; } ;
struct TYPE_21__ {unsigned int version; int hello_retry_request; TYPE_2__ ext; TYPE_7__* s3; TYPE_1__* method; int /*<<< orphan*/  tmp_session_id_len; int /*<<< orphan*/  tmp_session_id; TYPE_3__* ctx; TYPE_5__* session_ctx; } ;
struct TYPE_19__ {scalar_t__ new_cipher; } ;
struct TYPE_20__ {int flags; unsigned int group_id; TYPE_6__ tmp; } ;
struct TYPE_17__ {int /*<<< orphan*/  cookie_hmac_key; } ;
struct TYPE_18__ {TYPE_4__ ext; } ;
struct TYPE_16__ {scalar_t__ (* verify_stateless_cookie_cb ) (TYPE_8__*,unsigned char*,int) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  (* put_cipher_by_char ) (scalar_t__,int /*<<< orphan*/ *,size_t*) ;} ;
typedef  TYPE_8__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 unsigned int COOKIE_STATE_FORMAT_VERSION ; 
 scalar_t__ CRYPTO_memcmp (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ EVP_DigestSign (int /*<<< orphan*/ *,unsigned char*,size_t*,unsigned char const*,size_t) ; 
 scalar_t__ EVP_DigestSignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_HMAC ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new_raw_private_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int MAX_HRR_SIZE ; 
 int /*<<< orphan*/  PACKET_as_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_forward (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_net_4 (int /*<<< orphan*/ *,unsigned long*) ; 
 int PACKET_remaining (int /*<<< orphan*/ *) ; 
 int SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SSL3_MT_SERVER_HELLO ; 
 int /*<<< orphan*/  SSL3_RANDOM_SIZE ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_CTOS_COOKIE ; 
 int /*<<< orphan*/  SSL_R_BAD_CIPHER ; 
 int /*<<< orphan*/  SSL_R_BAD_PROTOCOL_VERSION_NUMBER ; 
 int /*<<< orphan*/  SSL_R_COOKIE_MISMATCH ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSLfatal (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int TLS1_2_VERSION ; 
 unsigned int TLS1_3_VERSION ; 
 int TLS1_FLAGS_STATELESS ; 
 unsigned int TLSEXT_TYPE_cookie ; 
 unsigned int TLSEXT_TYPE_key_share ; 
 unsigned int TLSEXT_TYPE_supported_versions ; 
 int /*<<< orphan*/  WPACKET_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_get_total_written (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  WPACKET_init_static_len (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u24 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u16 (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_synthetic_message_hash (TYPE_8__*,unsigned char*,int,unsigned char*,size_t) ; 
 int /*<<< orphan*/  hrrrandom ; 
 scalar_t__ ssl_get_cipher_by_char (TYPE_8__*,unsigned char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_8__*,unsigned char*,int) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int tls_parse_ctos_cookie(SSL *s, PACKET *pkt, unsigned int context, X509 *x,
                          size_t chainidx)
{
#ifndef OPENSSL_NO_TLS1_3
    unsigned int format, version, key_share, group_id;
    EVP_MD_CTX *hctx;
    EVP_PKEY *pkey;
    PACKET cookie, raw, chhash, appcookie;
    WPACKET hrrpkt;
    const unsigned char *data, *mdin, *ciphdata;
    unsigned char hmac[SHA256_DIGEST_LENGTH];
    unsigned char hrr[MAX_HRR_SIZE];
    size_t rawlen, hmaclen, hrrlen, ciphlen;
    unsigned long tm, now;

    /* Ignore any cookie if we're not set up to verify it */
    if (s->ctx->verify_stateless_cookie_cb == NULL
            || (s->s3->flags & TLS1_FLAGS_STATELESS) == 0)
        return 1;

    if (!PACKET_as_length_prefixed_2(pkt, &cookie)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }

    raw = cookie;
    data = PACKET_data(&raw);
    rawlen = PACKET_remaining(&raw);
    if (rawlen < SHA256_DIGEST_LENGTH
            || !PACKET_forward(&raw, rawlen - SHA256_DIGEST_LENGTH)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }
    mdin = PACKET_data(&raw);

    /* Verify the HMAC of the cookie */
    hctx = EVP_MD_CTX_create();
    pkey = EVP_PKEY_new_raw_private_key(EVP_PKEY_HMAC, NULL,
                                        s->session_ctx->ext.cookie_hmac_key,
                                        sizeof(s->session_ctx->ext
                                               .cookie_hmac_key));
    if (hctx == NULL || pkey == NULL) {
        EVP_MD_CTX_free(hctx);
        EVP_PKEY_free(pkey);
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 ERR_R_MALLOC_FAILURE);
        return 0;
    }

    hmaclen = SHA256_DIGEST_LENGTH;
    if (EVP_DigestSignInit(hctx, NULL, EVP_sha256(), NULL, pkey) <= 0
            || EVP_DigestSign(hctx, hmac, &hmaclen, data,
                              rawlen - SHA256_DIGEST_LENGTH) <= 0
            || hmaclen != SHA256_DIGEST_LENGTH) {
        EVP_MD_CTX_free(hctx);
        EVP_PKEY_free(pkey);
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    EVP_MD_CTX_free(hctx);
    EVP_PKEY_free(pkey);

    if (CRYPTO_memcmp(hmac, mdin, SHA256_DIGEST_LENGTH) != 0) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 SSL_R_COOKIE_MISMATCH);
        return 0;
    }

    if (!PACKET_get_net_2(&cookie, &format)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }
    /* Check the cookie format is something we recognise. Ignore it if not */
    if (format != COOKIE_STATE_FORMAT_VERSION)
        return 1;

    /*
     * The rest of these checks really shouldn't fail since we have verified the
     * HMAC above.
     */

    /* Check the version number is sane */
    if (!PACKET_get_net_2(&cookie, &version)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }
    if (version != TLS1_3_VERSION) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 SSL_R_BAD_PROTOCOL_VERSION_NUMBER);
        return 0;
    }

    if (!PACKET_get_net_2(&cookie, &group_id)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }

    ciphdata = PACKET_data(&cookie);
    if (!PACKET_forward(&cookie, 2)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }
    if (group_id != s->s3->group_id
            || s->s3->tmp.new_cipher
               != ssl_get_cipher_by_char(s, ciphdata, 0)) {
        /*
         * We chose a different cipher or group id this time around to what is
         * in the cookie. Something must have changed.
         */
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 SSL_R_BAD_CIPHER);
        return 0;
    }

    if (!PACKET_get_1(&cookie, &key_share)
            || !PACKET_get_net_4(&cookie, &tm)
            || !PACKET_get_length_prefixed_2(&cookie, &chhash)
            || !PACKET_get_length_prefixed_1(&cookie, &appcookie)
            || PACKET_remaining(&cookie) != SHA256_DIGEST_LENGTH) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }

    /* We tolerate a cookie age of up to 10 minutes (= 60 * 10 seconds) */
    now = (unsigned long)time(NULL);
    if (tm > now || (now - tm) > 600) {
        /* Cookie is stale. Ignore it */
        return 1;
    }

    /* Verify the app cookie */
    if (s->ctx->verify_stateless_cookie_cb(s, PACKET_data(&appcookie),
                                     PACKET_remaining(&appcookie)) == 0) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 SSL_R_COOKIE_MISMATCH);
        return 0;
    }

    /*
     * Reconstruct the HRR that we would have sent in response to the original
     * ClientHello so we can add it to the transcript hash.
     * Note: This won't work with custom HRR extensions
     */
    if (!WPACKET_init_static_len(&hrrpkt, hrr, sizeof(hrr), 0)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }
    if (!WPACKET_put_bytes_u8(&hrrpkt, SSL3_MT_SERVER_HELLO)
            || !WPACKET_start_sub_packet_u24(&hrrpkt)
            || !WPACKET_put_bytes_u16(&hrrpkt, TLS1_2_VERSION)
            || !WPACKET_memcpy(&hrrpkt, hrrrandom, SSL3_RANDOM_SIZE)
            || !WPACKET_sub_memcpy_u8(&hrrpkt, s->tmp_session_id,
                                      s->tmp_session_id_len)
            || !s->method->put_cipher_by_char(s->s3->tmp.new_cipher, &hrrpkt,
                                              &ciphlen)
            || !WPACKET_put_bytes_u8(&hrrpkt, 0)
            || !WPACKET_start_sub_packet_u16(&hrrpkt)) {
        WPACKET_cleanup(&hrrpkt);
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }
    if (!WPACKET_put_bytes_u16(&hrrpkt, TLSEXT_TYPE_supported_versions)
            || !WPACKET_start_sub_packet_u16(&hrrpkt)
            || !WPACKET_put_bytes_u16(&hrrpkt, s->version)
            || !WPACKET_close(&hrrpkt)) {
        WPACKET_cleanup(&hrrpkt);
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }
    if (key_share) {
        if (!WPACKET_put_bytes_u16(&hrrpkt, TLSEXT_TYPE_key_share)
                || !WPACKET_start_sub_packet_u16(&hrrpkt)
                || !WPACKET_put_bytes_u16(&hrrpkt, s->s3->group_id)
                || !WPACKET_close(&hrrpkt)) {
            WPACKET_cleanup(&hrrpkt);
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
    }
    if (!WPACKET_put_bytes_u16(&hrrpkt, TLSEXT_TYPE_cookie)
            || !WPACKET_start_sub_packet_u16(&hrrpkt)
            || !WPACKET_sub_memcpy_u16(&hrrpkt, data, rawlen)
            || !WPACKET_close(&hrrpkt) /* cookie extension */
            || !WPACKET_close(&hrrpkt) /* extension block */
            || !WPACKET_close(&hrrpkt) /* message */
            || !WPACKET_get_total_written(&hrrpkt, &hrrlen)
            || !WPACKET_finish(&hrrpkt)) {
        WPACKET_cleanup(&hrrpkt);
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_CTOS_COOKIE,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    /* Reconstruct the transcript hash */
    if (!create_synthetic_message_hash(s, PACKET_data(&chhash),
                                       PACKET_remaining(&chhash), hrr,
                                       hrrlen)) {
        /* SSLfatal() already called */
        return 0;
    }

    /* Act as if this ClientHello came after a HelloRetryRequest */
    s->hello_retry_request = 1;

    s->ext.cookieok = 1;
#endif

    return 1;
}
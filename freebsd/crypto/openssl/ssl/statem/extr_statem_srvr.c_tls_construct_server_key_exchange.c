#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_28__ {int /*<<< orphan*/ * psk_identity_hint; int /*<<< orphan*/ * (* dh_tmp_cb ) (TYPE_7__*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/ * dh_tmp; scalar_t__ dh_tmp_auto; } ;
struct TYPE_27__ {scalar_t__ sig; int /*<<< orphan*/  sigalg; } ;
struct TYPE_20__ {int /*<<< orphan*/ * B; int /*<<< orphan*/ * s; int /*<<< orphan*/ * g; int /*<<< orphan*/ * N; } ;
struct TYPE_26__ {TYPE_3__* init_buf; TYPE_6__* s3; TYPE_9__* cert; TYPE_1__ srp_ctx; } ;
struct TYPE_24__ {TYPE_2__* cert; TYPE_4__* new_cipher; int /*<<< orphan*/ * pkey; TYPE_8__* sigalg; } ;
struct TYPE_25__ {TYPE_5__ tmp; } ;
struct TYPE_23__ {unsigned long algorithm_mkey; int algorithm_auth; } ;
struct TYPE_22__ {scalar_t__ data; } ;
struct TYPE_21__ {int /*<<< orphan*/ * privatekey; } ;
typedef  TYPE_7__ SSL ;
typedef  TYPE_8__ SIGALG_LOOKUP ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  DH ;
typedef  TYPE_9__ CERT ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2bin (int /*<<< orphan*/  const*,unsigned char*) ; 
 size_t BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int EVP_DigestSign (int /*<<< orphan*/ *,unsigned char*,size_t*,unsigned char*,size_t) ; 
 scalar_t__ EVP_DigestSignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_CTX_set_rsa_pss_saltlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_RSA_PSS ; 
 int /*<<< orphan*/  EVP_PKEY_assign_DH (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_DH (int /*<<< orphan*/ *) ; 
 size_t EVP_PKEY_get1_tls_encodedpoint (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_security_bits (int /*<<< orphan*/ *) ; 
 size_t EVP_PKEY_size (int /*<<< orphan*/ *) ; 
 int NAMED_CURVE_TYPE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 size_t PSK_MAX_IDENTITY_LEN ; 
 int /*<<< orphan*/  RSA_PKCS1_PSS_PADDING ; 
 int /*<<< orphan*/  RSA_PSS_SALTLEN_DIGEST ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE ; 
 unsigned long SSL_PSK ; 
 int /*<<< orphan*/  SSL_R_DH_KEY_TOO_SMALL ; 
 int /*<<< orphan*/  SSL_R_MISSING_SRP_PARAM ; 
 int /*<<< orphan*/  SSL_R_MISSING_TMP_DH_KEY ; 
 int /*<<< orphan*/  SSL_R_UNKNOWN_KEY_EXCHANGE_TYPE ; 
 int /*<<< orphan*/  SSL_R_UNSUPPORTED_ELLIPTIC_CURVE ; 
 int /*<<< orphan*/  SSL_SECOP_TMP_DH ; 
 scalar_t__ SSL_USE_SIGALGS (TYPE_7__*) ; 
 int SSL_aNULL ; 
 int SSL_aSRP ; 
 unsigned long SSL_kDHE ; 
 unsigned long SSL_kDHEPSK ; 
 unsigned long SSL_kECDHE ; 
 unsigned long SSL_kECDHEPSK ; 
 unsigned long SSL_kPSK ; 
 unsigned long SSL_kRSAPSK ; 
 unsigned long SSL_kSRP ; 
 int /*<<< orphan*/  SSLfatal (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_allocate_bytes (int /*<<< orphan*/ *,size_t,unsigned char**) ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_get_length (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  WPACKET_get_total_written (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int) ; 
 int WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int WPACKET_start_sub_packet_u8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_sub_allocate_bytes_u16 (int /*<<< orphan*/ *,size_t,unsigned char**) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u8 (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  WPACKET_sub_reserve_bytes_u16 (int /*<<< orphan*/ *,size_t,unsigned char**) ; 
 size_t construct_key_exchange_tbs (TYPE_7__*,unsigned char**,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * ssl_dh_to_pkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ssl_generate_pkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ssl_generate_pkey_group (TYPE_7__*,int) ; 
 int /*<<< orphan*/ * ssl_get_auto_dh (TYPE_7__*) ; 
 int /*<<< orphan*/  ssl_security (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tls1_lookup_md (TYPE_8__ const*,int /*<<< orphan*/  const**) ; 
 int tls1_shared_group (TYPE_7__*,int) ; 

int tls_construct_server_key_exchange(SSL *s, WPACKET *pkt)
{
#ifndef OPENSSL_NO_DH
    EVP_PKEY *pkdh = NULL;
#endif
#ifndef OPENSSL_NO_EC
    unsigned char *encodedPoint = NULL;
    size_t encodedlen = 0;
    int curve_id = 0;
#endif
    const SIGALG_LOOKUP *lu = s->s3->tmp.sigalg;
    int i;
    unsigned long type;
    const BIGNUM *r[4];
    EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
    EVP_PKEY_CTX *pctx = NULL;
    size_t paramlen, paramoffset;

    if (!WPACKET_get_total_written(pkt, &paramoffset)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE, ERR_R_INTERNAL_ERROR);
        goto err;
    }

    if (md_ctx == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    type = s->s3->tmp.new_cipher->algorithm_mkey;

    r[0] = r[1] = r[2] = r[3] = NULL;
#ifndef OPENSSL_NO_PSK
    /* Plain PSK or RSAPSK nothing to do */
    if (type & (SSL_kPSK | SSL_kRSAPSK)) {
    } else
#endif                          /* !OPENSSL_NO_PSK */
#ifndef OPENSSL_NO_DH
    if (type & (SSL_kDHE | SSL_kDHEPSK)) {
        CERT *cert = s->cert;

        EVP_PKEY *pkdhp = NULL;
        DH *dh;

        if (s->cert->dh_tmp_auto) {
            DH *dhp = ssl_get_auto_dh(s);
            pkdh = EVP_PKEY_new();
            if (pkdh == NULL || dhp == NULL) {
                DH_free(dhp);
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                         ERR_R_INTERNAL_ERROR);
                goto err;
            }
            EVP_PKEY_assign_DH(pkdh, dhp);
            pkdhp = pkdh;
        } else {
            pkdhp = cert->dh_tmp;
        }
        if ((pkdhp == NULL) && (s->cert->dh_tmp_cb != NULL)) {
            DH *dhp = s->cert->dh_tmp_cb(s, 0, 1024);
            pkdh = ssl_dh_to_pkey(dhp);
            if (pkdh == NULL) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                         ERR_R_INTERNAL_ERROR);
                goto err;
            }
            pkdhp = pkdh;
        }
        if (pkdhp == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     SSL_R_MISSING_TMP_DH_KEY);
            goto err;
        }
        if (!ssl_security(s, SSL_SECOP_TMP_DH,
                          EVP_PKEY_security_bits(pkdhp), 0, pkdhp)) {
            SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     SSL_R_DH_KEY_TOO_SMALL);
            goto err;
        }
        if (s->s3->tmp.pkey != NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

        s->s3->tmp.pkey = ssl_generate_pkey(pkdhp);
        if (s->s3->tmp.pkey == NULL) {
            /* SSLfatal() already called */
            goto err;
        }

        dh = EVP_PKEY_get0_DH(s->s3->tmp.pkey);
        if (dh == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

        EVP_PKEY_free(pkdh);
        pkdh = NULL;

        DH_get0_pqg(dh, &r[0], NULL, &r[1]);
        DH_get0_key(dh, &r[2], NULL);
    } else
#endif
#ifndef OPENSSL_NO_EC
    if (type & (SSL_kECDHE | SSL_kECDHEPSK)) {

        if (s->s3->tmp.pkey != NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

        /* Get NID of appropriate shared curve */
        curve_id = tls1_shared_group(s, -2);
        if (curve_id == 0) {
            SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     SSL_R_UNSUPPORTED_ELLIPTIC_CURVE);
            goto err;
        }
        s->s3->tmp.pkey = ssl_generate_pkey_group(s, curve_id);
        /* Generate a new key for this curve */
        if (s->s3->tmp.pkey == NULL) {
            /* SSLfatal() already called */
            goto err;
        }

        /* Encode the public key. */
        encodedlen = EVP_PKEY_get1_tls_encodedpoint(s->s3->tmp.pkey,
                                                    &encodedPoint);
        if (encodedlen == 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE, ERR_R_EC_LIB);
            goto err;
        }

        /*
         * We'll generate the serverKeyExchange message explicitly so we
         * can set these to NULLs
         */
        r[0] = NULL;
        r[1] = NULL;
        r[2] = NULL;
        r[3] = NULL;
    } else
#endif                          /* !OPENSSL_NO_EC */
#ifndef OPENSSL_NO_SRP
    if (type & SSL_kSRP) {
        if ((s->srp_ctx.N == NULL) ||
            (s->srp_ctx.g == NULL) ||
            (s->srp_ctx.s == NULL) || (s->srp_ctx.B == NULL)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     SSL_R_MISSING_SRP_PARAM);
            goto err;
        }
        r[0] = s->srp_ctx.N;
        r[1] = s->srp_ctx.g;
        r[2] = s->srp_ctx.s;
        r[3] = s->srp_ctx.B;
    } else
#endif
    {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                 SSL_R_UNKNOWN_KEY_EXCHANGE_TYPE);
        goto err;
    }

    if (((s->s3->tmp.new_cipher->algorithm_auth & (SSL_aNULL | SSL_aSRP)) != 0)
        || ((s->s3->tmp.new_cipher->algorithm_mkey & SSL_PSK)) != 0) {
        lu = NULL;
    } else if (lu == NULL) {
        SSLfatal(s, SSL_AD_DECODE_ERROR,
                 SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE, ERR_R_INTERNAL_ERROR);
        goto err;
    }

#ifndef OPENSSL_NO_PSK
    if (type & SSL_PSK) {
        size_t len = (s->cert->psk_identity_hint == NULL)
                        ? 0 : strlen(s->cert->psk_identity_hint);

        /*
         * It should not happen that len > PSK_MAX_IDENTITY_LEN - we already
         * checked this when we set the identity hint - but just in case
         */
        if (len > PSK_MAX_IDENTITY_LEN
                || !WPACKET_sub_memcpy_u16(pkt, s->cert->psk_identity_hint,
                                           len)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
    }
#endif

    for (i = 0; i < 4 && r[i] != NULL; i++) {
        unsigned char *binval;
        int res;

#ifndef OPENSSL_NO_SRP
        if ((i == 2) && (type & SSL_kSRP)) {
            res = WPACKET_start_sub_packet_u8(pkt);
        } else
#endif
            res = WPACKET_start_sub_packet_u16(pkt);

        if (!res) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

#ifndef OPENSSL_NO_DH
        /*-
         * for interoperability with some versions of the Microsoft TLS
         * stack, we need to zero pad the DHE pub key to the same length
         * as the prime
         */
        if ((i == 2) && (type & (SSL_kDHE | SSL_kDHEPSK))) {
            size_t len = BN_num_bytes(r[0]) - BN_num_bytes(r[2]);

            if (len > 0) {
                if (!WPACKET_allocate_bytes(pkt, len, &binval)) {
                    SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                             SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                             ERR_R_INTERNAL_ERROR);
                    goto err;
                }
                memset(binval, 0, len);
            }
        }
#endif
        if (!WPACKET_allocate_bytes(pkt, BN_num_bytes(r[i]), &binval)
                || !WPACKET_close(pkt)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

        BN_bn2bin(r[i], binval);
    }

#ifndef OPENSSL_NO_EC
    if (type & (SSL_kECDHE | SSL_kECDHEPSK)) {
        /*
         * We only support named (not generic) curves. In this situation, the
         * ServerKeyExchange message has: [1 byte CurveType], [2 byte CurveName]
         * [1 byte length of encoded point], followed by the actual encoded
         * point itself
         */
        if (!WPACKET_put_bytes_u8(pkt, NAMED_CURVE_TYPE)
                || !WPACKET_put_bytes_u8(pkt, 0)
                || !WPACKET_put_bytes_u8(pkt, curve_id)
                || !WPACKET_sub_memcpy_u8(pkt, encodedPoint, encodedlen)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
        OPENSSL_free(encodedPoint);
        encodedPoint = NULL;
    }
#endif

    /* not anonymous */
    if (lu != NULL) {
        EVP_PKEY *pkey = s->s3->tmp.cert->privatekey;
        const EVP_MD *md;
        unsigned char *sigbytes1, *sigbytes2, *tbs;
        size_t siglen, tbslen;
        int rv;

        if (pkey == NULL || !tls1_lookup_md(lu, &md)) {
            /* Should never happen */
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
        /* Get length of the parameters we have written above */
        if (!WPACKET_get_length(pkt, &paramlen)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
        /* send signature algorithm */
        if (SSL_USE_SIGALGS(s) && !WPACKET_put_bytes_u16(pkt, lu->sigalg)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
        /*
         * Create the signature. We don't know the actual length of the sig
         * until after we've created it, so we reserve enough bytes for it
         * up front, and then properly allocate them in the WPACKET
         * afterwards.
         */
        siglen = EVP_PKEY_size(pkey);
        if (!WPACKET_sub_reserve_bytes_u16(pkt, siglen, &sigbytes1)
            || EVP_DigestSignInit(md_ctx, &pctx, md, NULL, pkey) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
        if (lu->sig == EVP_PKEY_RSA_PSS) {
            if (EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PSS_PADDING) <= 0
                || EVP_PKEY_CTX_set_rsa_pss_saltlen(pctx, RSA_PSS_SALTLEN_DIGEST) <= 0) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                        ERR_R_EVP_LIB);
                goto err;
            }
        }
        tbslen = construct_key_exchange_tbs(s, &tbs,
                                            s->init_buf->data + paramoffset,
                                            paramlen);
        if (tbslen == 0) {
            /* SSLfatal() already called */
            goto err;
        }
        rv = EVP_DigestSign(md_ctx, sigbytes1, &siglen, tbs, tbslen);
        OPENSSL_free(tbs);
        if (rv <= 0 || !WPACKET_sub_allocate_bytes_u16(pkt, siglen, &sigbytes2)
            || sigbytes1 != sigbytes2) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_SERVER_KEY_EXCHANGE,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
    }

    EVP_MD_CTX_free(md_ctx);
    return 1;
 err:
#ifndef OPENSSL_NO_DH
    EVP_PKEY_free(pkdh);
#endif
#ifndef OPENSSL_NO_EC
    OPENSSL_free(encodedPoint);
#endif
    EVP_MD_CTX_free(md_ctx);
    return 0;
}
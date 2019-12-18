#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  premaster_secret ;
struct TYPE_18__ {int no_cert_verify; } ;
struct TYPE_19__ {TYPE_7__ statem; TYPE_6__* session; TYPE_5__* cert; TYPE_3__* s3; } ;
struct TYPE_17__ {int /*<<< orphan*/  peer; } ;
struct TYPE_16__ {TYPE_4__* pkeys; } ;
struct TYPE_15__ {int /*<<< orphan*/ * privatekey; } ;
struct TYPE_13__ {TYPE_1__* new_cipher; } ;
struct TYPE_14__ {TYPE_2__ tmp; } ;
struct TYPE_12__ {unsigned long algorithm_auth; } ;
typedef  TYPE_8__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_PEER_KEY ; 
 scalar_t__ EVP_PKEY_CTX_ctrl (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_decrypt (int /*<<< orphan*/ *,unsigned char*,size_t*,unsigned char const*,size_t) ; 
 scalar_t__ EVP_PKEY_decrypt_init (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_derive_set_peer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_as_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_forward (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_peek_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 size_t PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_CKE_GOST ; 
 size_t SSL_PKEY_GOST01 ; 
 size_t SSL_PKEY_GOST12_256 ; 
 size_t SSL_PKEY_GOST12_512 ; 
 int /*<<< orphan*/  SSL_R_DECRYPTION_FAILED ; 
 unsigned long SSL_aGOST01 ; 
 unsigned long SSL_aGOST12 ; 
 int /*<<< orphan*/  SSLfatal (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int V_ASN1_CONSTRUCTED ; 
 unsigned int V_ASN1_SEQUENCE ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_generate_master_secret (TYPE_8__*,unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tls_process_cke_gost(SSL *s, PACKET *pkt)
{
#ifndef OPENSSL_NO_GOST
    EVP_PKEY_CTX *pkey_ctx;
    EVP_PKEY *client_pub_pkey = NULL, *pk = NULL;
    unsigned char premaster_secret[32];
    const unsigned char *start;
    size_t outlen = 32, inlen;
    unsigned long alg_a;
    unsigned int asn1id, asn1len;
    int ret = 0;
    PACKET encdata;

    /* Get our certificate private key */
    alg_a = s->s3->tmp.new_cipher->algorithm_auth;
    if (alg_a & SSL_aGOST12) {
        /*
         * New GOST ciphersuites have SSL_aGOST01 bit too
         */
        pk = s->cert->pkeys[SSL_PKEY_GOST12_512].privatekey;
        if (pk == NULL) {
            pk = s->cert->pkeys[SSL_PKEY_GOST12_256].privatekey;
        }
        if (pk == NULL) {
            pk = s->cert->pkeys[SSL_PKEY_GOST01].privatekey;
        }
    } else if (alg_a & SSL_aGOST01) {
        pk = s->cert->pkeys[SSL_PKEY_GOST01].privatekey;
    }

    pkey_ctx = EVP_PKEY_CTX_new(pk, NULL);
    if (pkey_ctx == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_GOST,
                 ERR_R_MALLOC_FAILURE);
        return 0;
    }
    if (EVP_PKEY_decrypt_init(pkey_ctx) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_GOST,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }
    /*
     * If client certificate is present and is of the same type, maybe
     * use it for key exchange.  Don't mind errors from
     * EVP_PKEY_derive_set_peer, because it is completely valid to use a
     * client certificate for authorization only.
     */
    client_pub_pkey = X509_get0_pubkey(s->session->peer);
    if (client_pub_pkey) {
        if (EVP_PKEY_derive_set_peer(pkey_ctx, client_pub_pkey) <= 0)
            ERR_clear_error();
    }
    /* Decrypt session key */
    if (!PACKET_get_1(pkt, &asn1id)
            || asn1id != (V_ASN1_SEQUENCE | V_ASN1_CONSTRUCTED)
            || !PACKET_peek_1(pkt, &asn1len)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CKE_GOST,
                 SSL_R_DECRYPTION_FAILED);
        goto err;
    }
    if (asn1len == 0x81) {
        /*
         * Long form length. Should only be one byte of length. Anything else
         * isn't supported.
         * We did a successful peek before so this shouldn't fail
         */
        if (!PACKET_forward(pkt, 1)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_GOST,
                     SSL_R_DECRYPTION_FAILED);
            goto err;
        }
    } else  if (asn1len >= 0x80) {
        /*
         * Indefinite length, or more than one long form length bytes. We don't
         * support it
         */
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CKE_GOST,
                 SSL_R_DECRYPTION_FAILED);
        goto err;
    } /* else short form length */

    if (!PACKET_as_length_prefixed_1(pkt, &encdata)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CKE_GOST,
                 SSL_R_DECRYPTION_FAILED);
        goto err;
    }
    inlen = PACKET_remaining(&encdata);
    start = PACKET_data(&encdata);

    if (EVP_PKEY_decrypt(pkey_ctx, premaster_secret, &outlen, start,
                         inlen) <= 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CKE_GOST,
                 SSL_R_DECRYPTION_FAILED);
        goto err;
    }
    /* Generate master secret */
    if (!ssl_generate_master_secret(s, premaster_secret,
                                    sizeof(premaster_secret), 0)) {
        /* SSLfatal() already called */
        goto err;
    }
    /* Check if pubkey from client certificate was used */
    if (EVP_PKEY_CTX_ctrl(pkey_ctx, -1, -1, EVP_PKEY_CTRL_PEER_KEY, 2,
                          NULL) > 0)
        s->statem.no_cert_verify = 1;

    ret = 1;
 err:
    EVP_PKEY_CTX_free(pkey_ctx);
    return ret;
#else
    /* Should never happen */
    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_GOST,
             ERR_R_INTERNAL_ERROR);
    return 0;
#endif
}
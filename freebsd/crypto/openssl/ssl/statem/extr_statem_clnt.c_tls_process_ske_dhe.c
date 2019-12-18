#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_4__* session; TYPE_3__* s3; } ;
struct TYPE_12__ {int /*<<< orphan*/  peer; } ;
struct TYPE_10__ {TYPE_1__* new_cipher; } ;
struct TYPE_11__ {TYPE_2__ tmp; int /*<<< orphan*/ * peer_tmp; } ;
struct TYPE_9__ {int algorithm_auth; } ;
typedef  TYPE_5__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ DH_check_params (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  DH_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DH_new () ; 
 int /*<<< orphan*/  DH_security_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_set0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ EVP_PKEY_assign_DH (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_SKE_DHE ; 
 int /*<<< orphan*/  SSL_R_BAD_DH_VALUE ; 
 int /*<<< orphan*/  SSL_R_DH_KEY_TOO_SMALL ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_SECOP_TMP_DH ; 
 int SSL_aDSS ; 
 int SSL_aRSA ; 
 int /*<<< orphan*/  SSLfatal (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_security (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tls_process_ske_dhe(SSL *s, PACKET *pkt, EVP_PKEY **pkey)
{
#ifndef OPENSSL_NO_DH
    PACKET prime, generator, pub_key;
    EVP_PKEY *peer_tmp = NULL;

    DH *dh = NULL;
    BIGNUM *p = NULL, *g = NULL, *bnpub_key = NULL;

    int check_bits = 0;

    if (!PACKET_get_length_prefixed_2(pkt, &prime)
        || !PACKET_get_length_prefixed_2(pkt, &generator)
        || !PACKET_get_length_prefixed_2(pkt, &pub_key)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_SKE_DHE,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }

    peer_tmp = EVP_PKEY_new();
    dh = DH_new();

    if (peer_tmp == NULL || dh == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_SKE_DHE,
                 ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* TODO(size_t): Convert these calls */
    p = BN_bin2bn(PACKET_data(&prime), (int)PACKET_remaining(&prime), NULL);
    g = BN_bin2bn(PACKET_data(&generator), (int)PACKET_remaining(&generator),
                  NULL);
    bnpub_key = BN_bin2bn(PACKET_data(&pub_key),
                          (int)PACKET_remaining(&pub_key), NULL);
    if (p == NULL || g == NULL || bnpub_key == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_SKE_DHE,
                 ERR_R_BN_LIB);
        goto err;
    }

    /* test non-zero pubkey */
    if (BN_is_zero(bnpub_key)) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PROCESS_SKE_DHE,
                 SSL_R_BAD_DH_VALUE);
        goto err;
    }

    if (!DH_set0_pqg(dh, p, NULL, g)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_SKE_DHE,
                 ERR_R_BN_LIB);
        goto err;
    }
    p = g = NULL;

    if (DH_check_params(dh, &check_bits) == 0 || check_bits != 0) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PROCESS_SKE_DHE,
                 SSL_R_BAD_DH_VALUE);
        goto err;
    }

    if (!DH_set0_key(dh, bnpub_key, NULL)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_SKE_DHE,
                 ERR_R_BN_LIB);
        goto err;
    }
    bnpub_key = NULL;

    if (!ssl_security(s, SSL_SECOP_TMP_DH, DH_security_bits(dh), 0, dh)) {
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_TLS_PROCESS_SKE_DHE,
                 SSL_R_DH_KEY_TOO_SMALL);
        goto err;
    }

    if (EVP_PKEY_assign_DH(peer_tmp, dh) == 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_SKE_DHE,
                 ERR_R_EVP_LIB);
        goto err;
    }

    s->s3->peer_tmp = peer_tmp;

    /*
     * FIXME: This makes assumptions about which ciphersuites come with
     * public keys. We should have a less ad-hoc way of doing this
     */
    if (s->s3->tmp.new_cipher->algorithm_auth & (SSL_aRSA | SSL_aDSS))
        *pkey = X509_get0_pubkey(s->session->peer);
    /* else anonymous DH, so no certificate or pkey. */

    return 1;

 err:
    BN_free(p);
    BN_free(g);
    BN_free(bnpub_key);
    DH_free(dh);
    EVP_PKEY_free(peer_tmp);

    return 0;
#else
    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_SKE_DHE,
             ERR_R_INTERNAL_ERROR);
    return 0;
#endif
}
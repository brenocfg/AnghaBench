#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* s3; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pkey; } ;
struct TYPE_8__ {TYPE_1__ tmp; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 scalar_t__ EVP_PKEY_copy_parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 scalar_t__ EVP_PKEY_set1_tls_encodedpoint (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_bytes (int /*<<< orphan*/ *,unsigned char const**,unsigned int) ; 
 long PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_CKE_ECDHE ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_R_MISSING_TMP_ECDH_KEY ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ssl_derive (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tls_process_cke_ecdhe(SSL *s, PACKET *pkt)
{
#ifndef OPENSSL_NO_EC
    EVP_PKEY *skey = s->s3->tmp.pkey;
    EVP_PKEY *ckey = NULL;
    int ret = 0;

    if (PACKET_remaining(pkt) == 0L) {
        /* We don't support ECDH client auth */
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_TLS_PROCESS_CKE_ECDHE,
                 SSL_R_MISSING_TMP_ECDH_KEY);
        goto err;
    } else {
        unsigned int i;
        const unsigned char *data;

        /*
         * Get client's public key from encoded point in the
         * ClientKeyExchange message.
         */

        /* Get encoded point length */
        if (!PACKET_get_1(pkt, &i) || !PACKET_get_bytes(pkt, &data, i)
            || PACKET_remaining(pkt) != 0) {
            SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CKE_ECDHE,
                     SSL_R_LENGTH_MISMATCH);
            goto err;
        }
        if (skey == NULL) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_ECDHE,
                     SSL_R_MISSING_TMP_ECDH_KEY);
            goto err;
        }

        ckey = EVP_PKEY_new();
        if (ckey == NULL || EVP_PKEY_copy_parameters(ckey, skey) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_ECDHE,
                     ERR_R_EVP_LIB);
            goto err;
        }
        if (EVP_PKEY_set1_tls_encodedpoint(ckey, data, i) == 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_ECDHE,
                     ERR_R_EC_LIB);
            goto err;
        }
    }

    if (ssl_derive(s, skey, ckey, 1) == 0) {
        /* SSLfatal() already called */
        goto err;
    }

    ret = 1;
    EVP_PKEY_free(s->s3->tmp.pkey);
    s->s3->tmp.pkey = NULL;
 err:
    EVP_PKEY_free(ckey);

    return ret;
#else
    /* Should never happen */
    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_ECDHE,
             ERR_R_INTERNAL_ERROR);
    return 0;
#endif
}
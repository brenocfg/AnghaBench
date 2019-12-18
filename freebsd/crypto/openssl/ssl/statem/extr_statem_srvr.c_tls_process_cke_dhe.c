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
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char const*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 scalar_t__ EVP_PKEY_copy_parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_DH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  PACKET_get_bytes (int /*<<< orphan*/ *,unsigned char const**,unsigned int) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 long PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_CKE_DHE ; 
 int /*<<< orphan*/  SSL_R_BN_LIB ; 
 int /*<<< orphan*/  SSL_R_DH_PUBLIC_VALUE_LENGTH_IS_WRONG ; 
 int /*<<< orphan*/  SSL_R_MISSING_TMP_DH_KEY ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ssl_derive (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tls_process_cke_dhe(SSL *s, PACKET *pkt)
{
#ifndef OPENSSL_NO_DH
    EVP_PKEY *skey = NULL;
    DH *cdh;
    unsigned int i;
    BIGNUM *pub_key;
    const unsigned char *data;
    EVP_PKEY *ckey = NULL;
    int ret = 0;

    if (!PACKET_get_net_2(pkt, &i) || PACKET_remaining(pkt) != i) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CKE_DHE,
               SSL_R_DH_PUBLIC_VALUE_LENGTH_IS_WRONG);
        goto err;
    }
    skey = s->s3->tmp.pkey;
    if (skey == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_DHE,
                 SSL_R_MISSING_TMP_DH_KEY);
        goto err;
    }

    if (PACKET_remaining(pkt) == 0L) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_CKE_DHE,
                 SSL_R_MISSING_TMP_DH_KEY);
        goto err;
    }
    if (!PACKET_get_bytes(pkt, &data, i)) {
        /* We already checked we have enough data */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_DHE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }
    ckey = EVP_PKEY_new();
    if (ckey == NULL || EVP_PKEY_copy_parameters(ckey, skey) == 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_DHE,
                 SSL_R_BN_LIB);
        goto err;
    }

    cdh = EVP_PKEY_get0_DH(ckey);
    pub_key = BN_bin2bn(data, i, NULL);
    if (pub_key == NULL || cdh == NULL || !DH_set0_key(cdh, pub_key, NULL)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_DHE,
                 ERR_R_INTERNAL_ERROR);
        BN_free(pub_key);
        goto err;
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
    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_CKE_DHE,
             ERR_R_INTERNAL_ERROR);
    return 0;
#endif
}
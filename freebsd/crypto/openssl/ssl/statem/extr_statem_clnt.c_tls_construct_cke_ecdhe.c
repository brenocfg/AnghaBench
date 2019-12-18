#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_7__ {TYPE_1__* s3; } ;
struct TYPE_6__ {int /*<<< orphan*/ * peer_tmp; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 size_t EVP_PKEY_get1_tls_encodedpoint (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CKE_ECDHE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u8 (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 scalar_t__ ssl_derive (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ssl_generate_pkey (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tls_construct_cke_ecdhe(SSL *s, WPACKET *pkt)
{
#ifndef OPENSSL_NO_EC
    unsigned char *encodedPoint = NULL;
    size_t encoded_pt_len = 0;
    EVP_PKEY *ckey = NULL, *skey = NULL;
    int ret = 0;

    skey = s->s3->peer_tmp;
    if (skey == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_ECDHE,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    ckey = ssl_generate_pkey(skey);
    if (ckey == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_ECDHE,
                 ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (ssl_derive(s, ckey, skey, 0) == 0) {
        /* SSLfatal() already called */
        goto err;
    }

    /* Generate encoding of client key */
    encoded_pt_len = EVP_PKEY_get1_tls_encodedpoint(ckey, &encodedPoint);

    if (encoded_pt_len == 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_ECDHE,
                 ERR_R_EC_LIB);
        goto err;
    }

    if (!WPACKET_sub_memcpy_u8(pkt, encodedPoint, encoded_pt_len)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_ECDHE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    ret = 1;
 err:
    OPENSSL_free(encodedPoint);
    EVP_PKEY_free(ckey);
    return ret;
#else
    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_ECDHE,
             ERR_R_INTERNAL_ERROR);
    return 0;
#endif
}
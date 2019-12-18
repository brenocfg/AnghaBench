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
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2bin (int /*<<< orphan*/  const*,unsigned char*) ; 
 int /*<<< orphan*/  BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DH_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get0_DH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CKE_DHE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_sub_allocate_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char**) ; 
 scalar_t__ ssl_derive (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ssl_generate_pkey (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tls_construct_cke_dhe(SSL *s, WPACKET *pkt)
{
#ifndef OPENSSL_NO_DH
    DH *dh_clnt = NULL;
    const BIGNUM *pub_key;
    EVP_PKEY *ckey = NULL, *skey = NULL;
    unsigned char *keybytes = NULL;

    skey = s->s3->peer_tmp;
    if (skey == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_DHE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    ckey = ssl_generate_pkey(skey);
    if (ckey == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_DHE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    dh_clnt = EVP_PKEY_get0_DH(ckey);

    if (dh_clnt == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_DHE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    if (ssl_derive(s, ckey, skey, 0) == 0) {
        /* SSLfatal() already called */
        goto err;
    }

    /* send off the data */
    DH_get0_key(dh_clnt, &pub_key, NULL);
    if (!WPACKET_sub_allocate_bytes_u16(pkt, BN_num_bytes(pub_key),
                                        &keybytes)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_DHE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    BN_bn2bin(pub_key, keybytes);
    EVP_PKEY_free(ckey);

    return 1;
 err:
    EVP_PKEY_free(ckey);
    return 0;
#else
    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_DHE,
             ERR_R_INTERNAL_ERROR);
    return 0;
#endif
}
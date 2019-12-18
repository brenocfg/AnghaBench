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
typedef  int uint32_t ;
struct TYPE_13__ {TYPE_1__* pkeys; scalar_t__ dh_tmp_auto; int /*<<< orphan*/ * dh_tmp_cb; int /*<<< orphan*/ * dh_tmp; } ;
struct TYPE_12__ {TYPE_3__* s3; TYPE_5__* cert; } ;
struct TYPE_10__ {int* valid_flags; unsigned long mask_k; unsigned long mask_a; } ;
struct TYPE_11__ {TYPE_2__ tmp; } ;
struct TYPE_9__ {int /*<<< orphan*/  x509; } ;
typedef  TYPE_4__ SSL ;
typedef  TYPE_5__ CERT ;

/* Variables and functions */
 int CERT_PKEY_EXPLICIT_SIGN ; 
 int CERT_PKEY_SIGN ; 
 int CERT_PKEY_VALID ; 
 size_t SSL_PKEY_DSA_SIGN ; 
 size_t SSL_PKEY_ECC ; 
 size_t SSL_PKEY_ED25519 ; 
 size_t SSL_PKEY_ED448 ; 
 size_t SSL_PKEY_GOST01 ; 
 size_t SSL_PKEY_GOST12_256 ; 
 size_t SSL_PKEY_GOST12_512 ; 
 size_t SSL_PKEY_RSA ; 
 size_t SSL_PKEY_RSA_PSS_SIGN ; 
 unsigned long SSL_aDSS ; 
 unsigned long SSL_aECDSA ; 
 unsigned long SSL_aGOST01 ; 
 unsigned long SSL_aGOST12 ; 
 unsigned long SSL_aNULL ; 
 unsigned long SSL_aPSK ; 
 unsigned long SSL_aRSA ; 
 unsigned long SSL_kDHE ; 
 unsigned long SSL_kDHEPSK ; 
 unsigned long SSL_kECDHE ; 
 unsigned long SSL_kECDHEPSK ; 
 unsigned long SSL_kGOST ; 
 unsigned long SSL_kPSK ; 
 unsigned long SSL_kRSA ; 
 unsigned long SSL_kRSAPSK ; 
 scalar_t__ TLS1_2_VERSION ; 
 scalar_t__ TLS1_get_version (TYPE_4__*) ; 
 int X509_get_key_usage (int /*<<< orphan*/ ) ; 
 int X509v3_KU_DIGITAL_SIGNATURE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 scalar_t__ ssl_has_cert (TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  stderr ; 

void ssl_set_masks(SSL *s)
{
    CERT *c = s->cert;
    uint32_t *pvalid = s->s3->tmp.valid_flags;
    int rsa_enc, rsa_sign, dh_tmp, dsa_sign;
    unsigned long mask_k, mask_a;
#ifndef OPENSSL_NO_EC
    int have_ecc_cert, ecdsa_ok;
#endif
    if (c == NULL)
        return;

#ifndef OPENSSL_NO_DH
    dh_tmp = (c->dh_tmp != NULL || c->dh_tmp_cb != NULL || c->dh_tmp_auto);
#else
    dh_tmp = 0;
#endif

    rsa_enc = pvalid[SSL_PKEY_RSA] & CERT_PKEY_VALID;
    rsa_sign = pvalid[SSL_PKEY_RSA] & CERT_PKEY_VALID;
    dsa_sign = pvalid[SSL_PKEY_DSA_SIGN] & CERT_PKEY_VALID;
#ifndef OPENSSL_NO_EC
    have_ecc_cert = pvalid[SSL_PKEY_ECC] & CERT_PKEY_VALID;
#endif
    mask_k = 0;
    mask_a = 0;

#ifdef CIPHER_DEBUG
    fprintf(stderr, "dht=%d re=%d rs=%d ds=%d\n",
            dh_tmp, rsa_enc, rsa_sign, dsa_sign);
#endif

#ifndef OPENSSL_NO_GOST
    if (ssl_has_cert(s, SSL_PKEY_GOST12_512)) {
        mask_k |= SSL_kGOST;
        mask_a |= SSL_aGOST12;
    }
    if (ssl_has_cert(s, SSL_PKEY_GOST12_256)) {
        mask_k |= SSL_kGOST;
        mask_a |= SSL_aGOST12;
    }
    if (ssl_has_cert(s, SSL_PKEY_GOST01)) {
        mask_k |= SSL_kGOST;
        mask_a |= SSL_aGOST01;
    }
#endif

    if (rsa_enc)
        mask_k |= SSL_kRSA;

    if (dh_tmp)
        mask_k |= SSL_kDHE;

    /*
     * If we only have an RSA-PSS certificate allow RSA authentication
     * if TLS 1.2 and peer supports it.
     */

    if (rsa_enc || rsa_sign || (ssl_has_cert(s, SSL_PKEY_RSA_PSS_SIGN)
                && pvalid[SSL_PKEY_RSA_PSS_SIGN] & CERT_PKEY_EXPLICIT_SIGN
                && TLS1_get_version(s) == TLS1_2_VERSION))
        mask_a |= SSL_aRSA;

    if (dsa_sign) {
        mask_a |= SSL_aDSS;
    }

    mask_a |= SSL_aNULL;

    /*
     * An ECC certificate may be usable for ECDH and/or ECDSA cipher suites
     * depending on the key usage extension.
     */
#ifndef OPENSSL_NO_EC
    if (have_ecc_cert) {
        uint32_t ex_kusage;
        ex_kusage = X509_get_key_usage(c->pkeys[SSL_PKEY_ECC].x509);
        ecdsa_ok = ex_kusage & X509v3_KU_DIGITAL_SIGNATURE;
        if (!(pvalid[SSL_PKEY_ECC] & CERT_PKEY_SIGN))
            ecdsa_ok = 0;
        if (ecdsa_ok)
            mask_a |= SSL_aECDSA;
    }
    /* Allow Ed25519 for TLS 1.2 if peer supports it */
    if (!(mask_a & SSL_aECDSA) && ssl_has_cert(s, SSL_PKEY_ED25519)
            && pvalid[SSL_PKEY_ED25519] & CERT_PKEY_EXPLICIT_SIGN
            && TLS1_get_version(s) == TLS1_2_VERSION)
            mask_a |= SSL_aECDSA;

    /* Allow Ed448 for TLS 1.2 if peer supports it */
    if (!(mask_a & SSL_aECDSA) && ssl_has_cert(s, SSL_PKEY_ED448)
            && pvalid[SSL_PKEY_ED448] & CERT_PKEY_EXPLICIT_SIGN
            && TLS1_get_version(s) == TLS1_2_VERSION)
            mask_a |= SSL_aECDSA;
#endif

#ifndef OPENSSL_NO_EC
    mask_k |= SSL_kECDHE;
#endif

#ifndef OPENSSL_NO_PSK
    mask_k |= SSL_kPSK;
    mask_a |= SSL_aPSK;
    if (mask_k & SSL_kRSA)
        mask_k |= SSL_kRSAPSK;
    if (mask_k & SSL_kDHE)
        mask_k |= SSL_kDHEPSK;
    if (mask_k & SSL_kECDHE)
        mask_k |= SSL_kECDHEPSK;
#endif

    s->s3->tmp.mask_k = mask_k;
    s->s3->tmp.mask_a = mask_a;
}
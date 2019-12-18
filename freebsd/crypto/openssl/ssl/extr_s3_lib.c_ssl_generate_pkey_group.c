#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  nid; } ;
typedef  TYPE_1__ TLS_GROUP_INFO ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_set_ec_paramgen_curve_nid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_EC ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_keygen (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ EVP_PKEY_keygen_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL_GENERATE_PKEY_GROUP ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLS_CURVE_CUSTOM ; 
 int TLS_CURVE_TYPE ; 
 TYPE_1__* tls1_group_id_lookup (int) ; 

EVP_PKEY *ssl_generate_pkey_group(SSL *s, uint16_t id)
{
    EVP_PKEY_CTX *pctx = NULL;
    EVP_PKEY *pkey = NULL;
    const TLS_GROUP_INFO *ginf = tls1_group_id_lookup(id);
    uint16_t gtype;

    if (ginf == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GENERATE_PKEY_GROUP,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }
    gtype = ginf->flags & TLS_CURVE_TYPE;
    if (gtype == TLS_CURVE_CUSTOM)
        pctx = EVP_PKEY_CTX_new_id(ginf->nid, NULL);
    else
        pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL);
    if (pctx == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GENERATE_PKEY_GROUP,
                 ERR_R_MALLOC_FAILURE);
        goto err;
    }
    if (EVP_PKEY_keygen_init(pctx) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GENERATE_PKEY_GROUP,
                 ERR_R_EVP_LIB);
        goto err;
    }
    if (gtype != TLS_CURVE_CUSTOM
            && EVP_PKEY_CTX_set_ec_paramgen_curve_nid(pctx, ginf->nid) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GENERATE_PKEY_GROUP,
                 ERR_R_EVP_LIB);
        goto err;
    }
    if (EVP_PKEY_keygen(pctx, &pkey) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_GENERATE_PKEY_GROUP,
                 ERR_R_EVP_LIB);
        EVP_PKEY_free(pkey);
        pkey = NULL;
    }

 err:
    EVP_PKEY_CTX_free(pctx);
    return pkey;
}
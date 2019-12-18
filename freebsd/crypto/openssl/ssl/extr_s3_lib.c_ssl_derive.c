#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* s3; int /*<<< orphan*/  early_secret; int /*<<< orphan*/  hit; } ;
struct TYPE_11__ {unsigned char* pms; size_t pmslen; } ;
struct TYPE_12__ {TYPE_1__ tmp; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_derive (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 scalar_t__ EVP_PKEY_derive_init (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_derive_set_peer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL_DERIVE ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_3__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ssl_generate_master_secret (TYPE_3__*,unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_handshake_md (TYPE_3__*) ; 
 scalar_t__ tls13_generate_handshake_secret (TYPE_3__*,unsigned char*,size_t) ; 
 int tls13_generate_secret (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 

int ssl_derive(SSL *s, EVP_PKEY *privkey, EVP_PKEY *pubkey, int gensecret)
{
    int rv = 0;
    unsigned char *pms = NULL;
    size_t pmslen = 0;
    EVP_PKEY_CTX *pctx;

    if (privkey == NULL || pubkey == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_DERIVE,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    pctx = EVP_PKEY_CTX_new(privkey, NULL);

    if (EVP_PKEY_derive_init(pctx) <= 0
        || EVP_PKEY_derive_set_peer(pctx, pubkey) <= 0
        || EVP_PKEY_derive(pctx, NULL, &pmslen) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_DERIVE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    pms = OPENSSL_malloc(pmslen);
    if (pms == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_DERIVE,
                 ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (EVP_PKEY_derive(pctx, pms, &pmslen) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_DERIVE,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    if (gensecret) {
        /* SSLfatal() called as appropriate in the below functions */
        if (SSL_IS_TLS13(s)) {
            /*
             * If we are resuming then we already generated the early secret
             * when we created the ClientHello, so don't recreate it.
             */
            if (!s->hit)
                rv = tls13_generate_secret(s, ssl_handshake_md(s), NULL, NULL,
                                           0,
                                           (unsigned char *)&s->early_secret);
            else
                rv = 1;

            rv = rv && tls13_generate_handshake_secret(s, pms, pmslen);
        } else {
            rv = ssl_generate_master_secret(s, pms, pmslen, 0);
        }
    } else {
        /* Save premaster secret */
        s->s3->tmp.pms = pms;
        s->s3->tmp.pmslen = pmslen;
        pms = NULL;
        rv = 1;
    }

 err:
    OPENSSL_clear_free(pms, pmslen);
    EVP_PKEY_CTX_free(pctx);
    return rv;
}
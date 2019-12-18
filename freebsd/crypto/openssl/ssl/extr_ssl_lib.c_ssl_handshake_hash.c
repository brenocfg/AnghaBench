#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* s3; } ;
struct TYPE_5__ {int /*<<< orphan*/ * handshake_dgst; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 scalar_t__ EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_copy_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int EVP_MD_CTX_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL_HANDSHAKE_HASH ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ssl_handshake_hash(SSL *s, unsigned char *out, size_t outlen,
                       size_t *hashlen)
{
    EVP_MD_CTX *ctx = NULL;
    EVP_MD_CTX *hdgst = s->s3->handshake_dgst;
    int hashleni = EVP_MD_CTX_size(hdgst);
    int ret = 0;

    if (hashleni < 0 || (size_t)hashleni > outlen) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_HANDSHAKE_HASH,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    ctx = EVP_MD_CTX_new();
    if (ctx == NULL)
        goto err;

    if (!EVP_MD_CTX_copy_ex(ctx, hdgst)
        || EVP_DigestFinal_ex(ctx, out, NULL) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL_HANDSHAKE_HASH,
                 ERR_R_INTERNAL_ERROR);
        goto err;
    }

    *hashlen = hashleni;

    ret = 1;
 err:
    EVP_MD_CTX_free(ctx);
    return ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {TYPE_2__* ctx; TYPE_1__* s3; } ;
struct TYPE_7__ {int /*<<< orphan*/  md5; int /*<<< orphan*/  sha1; } ;
struct TYPE_6__ {unsigned char* client_random; unsigned char* server_random; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 scalar_t__ EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 unsigned int SSL3_RANDOM_SIZE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL3_GENERATE_MASTER_SECRET ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int strlen (char const*) ; 

int ssl3_generate_master_secret(SSL *s, unsigned char *out, unsigned char *p,
                                size_t len, size_t *secret_size)
{
    static const unsigned char *salt[3] = {
#ifndef CHARSET_EBCDIC
        (const unsigned char *)"A",
        (const unsigned char *)"BB",
        (const unsigned char *)"CCC",
#else
        (const unsigned char *)"\x41",
        (const unsigned char *)"\x42\x42",
        (const unsigned char *)"\x43\x43\x43",
#endif
    };
    unsigned char buf[EVP_MAX_MD_SIZE];
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    int i, ret = 1;
    unsigned int n;
    size_t ret_secret_size = 0;

    if (ctx == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_GENERATE_MASTER_SECRET,
                 ERR_R_MALLOC_FAILURE);
        return 0;
    }
    for (i = 0; i < 3; i++) {
        if (EVP_DigestInit_ex(ctx, s->ctx->sha1, NULL) <= 0
            || EVP_DigestUpdate(ctx, salt[i],
                                strlen((const char *)salt[i])) <= 0
            || EVP_DigestUpdate(ctx, p, len) <= 0
            || EVP_DigestUpdate(ctx, &(s->s3->client_random[0]),
                                SSL3_RANDOM_SIZE) <= 0
            || EVP_DigestUpdate(ctx, &(s->s3->server_random[0]),
                                SSL3_RANDOM_SIZE) <= 0
               /* TODO(size_t) : convert me */
            || EVP_DigestFinal_ex(ctx, buf, &n) <= 0
            || EVP_DigestInit_ex(ctx, s->ctx->md5, NULL) <= 0
            || EVP_DigestUpdate(ctx, p, len) <= 0
            || EVP_DigestUpdate(ctx, buf, n) <= 0
            || EVP_DigestFinal_ex(ctx, out, &n) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_SSL3_GENERATE_MASTER_SECRET, ERR_R_INTERNAL_ERROR);
            ret = 0;
            break;
        }
        out += n;
        ret_secret_size += n;
    }
    EVP_MD_CTX_free(ctx);

    OPENSSL_cleanse(buf, sizeof(buf));
    if (ret)
        *secret_size = ret_secret_size;
    return ret;
}
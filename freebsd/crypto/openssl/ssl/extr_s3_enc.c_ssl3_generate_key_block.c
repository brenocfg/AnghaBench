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
typedef  int /*<<< orphan*/  smd ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {TYPE_2__* session; TYPE_1__* s3; } ;
struct TYPE_7__ {unsigned char* master_key; int master_key_length; } ;
struct TYPE_6__ {unsigned char* server_random; unsigned char* client_random; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_NON_FIPS_ALLOW ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 scalar_t__ MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int SHA_DIGEST_LENGTH ; 
 int SSL3_RANDOM_SIZE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SSL3_GENERATE_KEY_BLOCK ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 unsigned char* os_toascii ; 

__attribute__((used)) static int ssl3_generate_key_block(SSL *s, unsigned char *km, int num)
{
    EVP_MD_CTX *m5;
    EVP_MD_CTX *s1;
    unsigned char buf[16], smd[SHA_DIGEST_LENGTH];
    unsigned char c = 'A';
    unsigned int i, j, k;
    int ret = 0;

#ifdef CHARSET_EBCDIC
    c = os_toascii[c];          /* 'A' in ASCII */
#endif
    k = 0;
    m5 = EVP_MD_CTX_new();
    s1 = EVP_MD_CTX_new();
    if (m5 == NULL || s1 == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_GENERATE_KEY_BLOCK,
                 ERR_R_MALLOC_FAILURE);
        goto err;
    }
    EVP_MD_CTX_set_flags(m5, EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
    for (i = 0; (int)i < num; i += MD5_DIGEST_LENGTH) {
        k++;
        if (k > sizeof(buf)) {
            /* bug: 'buf' is too small for this ciphersuite */
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_GENERATE_KEY_BLOCK,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }

        for (j = 0; j < k; j++)
            buf[j] = c;
        c++;
        if (!EVP_DigestInit_ex(s1, EVP_sha1(), NULL)
            || !EVP_DigestUpdate(s1, buf, k)
            || !EVP_DigestUpdate(s1, s->session->master_key,
                                 s->session->master_key_length)
            || !EVP_DigestUpdate(s1, s->s3->server_random, SSL3_RANDOM_SIZE)
            || !EVP_DigestUpdate(s1, s->s3->client_random, SSL3_RANDOM_SIZE)
            || !EVP_DigestFinal_ex(s1, smd, NULL)
            || !EVP_DigestInit_ex(m5, EVP_md5(), NULL)
            || !EVP_DigestUpdate(m5, s->session->master_key,
                                 s->session->master_key_length)
            || !EVP_DigestUpdate(m5, smd, SHA_DIGEST_LENGTH)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_SSL3_GENERATE_KEY_BLOCK,
                     ERR_R_INTERNAL_ERROR);
            goto err;
        }
        if ((int)(i + MD5_DIGEST_LENGTH) > num) {
            if (!EVP_DigestFinal_ex(m5, smd, NULL)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_SSL3_GENERATE_KEY_BLOCK, ERR_R_INTERNAL_ERROR);
                goto err;
            }
            memcpy(km, smd, (num - i));
        } else {
            if (!EVP_DigestFinal_ex(m5, km, NULL)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_SSL3_GENERATE_KEY_BLOCK, ERR_R_INTERNAL_ERROR);
                goto err;
            }
        }

        km += MD5_DIGEST_LENGTH;
    }
    OPENSSL_cleanse(smd, sizeof(smd));
    ret = 1;
 err:
    EVP_MD_CTX_free(m5);
    EVP_MD_CTX_free(s1);
    return ret;
}
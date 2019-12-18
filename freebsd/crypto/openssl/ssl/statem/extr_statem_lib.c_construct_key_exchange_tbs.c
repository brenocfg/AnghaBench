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
struct TYPE_5__ {void const* client_random; void const* server_random; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int SSL3_RANDOM_SIZE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_CONSTRUCT_KEY_EXCHANGE_TBS ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,size_t) ; 

size_t construct_key_exchange_tbs(SSL *s, unsigned char **ptbs,
                                  const void *param, size_t paramlen)
{
    size_t tbslen = 2 * SSL3_RANDOM_SIZE + paramlen;
    unsigned char *tbs = OPENSSL_malloc(tbslen);

    if (tbs == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_CONSTRUCT_KEY_EXCHANGE_TBS,
                 ERR_R_MALLOC_FAILURE);
        return 0;
    }
    memcpy(tbs, s->s3->client_random, SSL3_RANDOM_SIZE);
    memcpy(tbs + SSL3_RANDOM_SIZE, s->s3->server_random, SSL3_RANDOM_SIZE);

    memcpy(tbs + SSL3_RANDOM_SIZE * 2, param, paramlen);

    *ptbs = tbs;
    return tbslen;
}
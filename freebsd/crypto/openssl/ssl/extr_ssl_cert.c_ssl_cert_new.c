#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int references; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * sec_ex; int /*<<< orphan*/  sec_level; int /*<<< orphan*/  sec_cb; int /*<<< orphan*/ * pkeys; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ CERT ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_TLS_SECURITY_LEVEL ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  SSL_F_SSL_CERT_NEW ; 
 size_t SSL_PKEY_RSA ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_security_default_callback ; 

CERT *ssl_cert_new(void)
{
    CERT *ret = OPENSSL_zalloc(sizeof(*ret));

    if (ret == NULL) {
        SSLerr(SSL_F_SSL_CERT_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    ret->key = &(ret->pkeys[SSL_PKEY_RSA]);
    ret->references = 1;
    ret->sec_cb = ssl_security_default_callback;
    ret->sec_level = OPENSSL_TLS_SECURITY_LEVEL;
    ret->sec_ex = NULL;
    ret->lock = CRYPTO_THREAD_lock_new();
    if (ret->lock == NULL) {
        SSLerr(SSL_F_SSL_CERT_NEW, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(ret);
        return NULL;
    }

    return ret;
}
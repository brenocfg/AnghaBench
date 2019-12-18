#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int verify_result; int references; int timeout; unsigned long time; int /*<<< orphan*/ * lock; int /*<<< orphan*/  ex_data; } ;
typedef  TYPE_1__ SSL_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_EX_INDEX_SSL_SESSION ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  CRYPTO_new_ex_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_SSL_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  OPENSSL_init_ssl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  SSL_F_SSL_SESSION_NEW ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

SSL_SESSION *SSL_SESSION_new(void)
{
    SSL_SESSION *ss;

    if (!OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS, NULL))
        return NULL;

    ss = OPENSSL_zalloc(sizeof(*ss));
    if (ss == NULL) {
        SSLerr(SSL_F_SSL_SESSION_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    ss->verify_result = 1;      /* avoid 0 (= X509_V_OK) just in case */
    ss->references = 1;
    ss->timeout = 60 * 5 + 4;   /* 5 minute timeout by default */
    ss->time = (unsigned long)time(NULL);
    ss->lock = CRYPTO_THREAD_lock_new();
    if (ss->lock == NULL) {
        SSLerr(SSL_F_SSL_SESSION_NEW, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(ss);
        return NULL;
    }

    if (!CRYPTO_new_ex_data(CRYPTO_EX_INDEX_SSL_SESSION, ss, &ss->ex_data)) {
        CRYPTO_THREAD_lock_free(ss->lock);
        OPENSSL_free(ss);
        return NULL;
    }
    return ss;
}
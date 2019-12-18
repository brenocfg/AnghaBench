#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  OPENSSL_INIT_SETTINGS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INIT_FAIL ; 
 int OPENSSL_INIT_ADD_ALL_CIPHERS ; 
 int OPENSSL_INIT_ADD_ALL_DIGESTS ; 
 int OPENSSL_INIT_LOAD_CONFIG ; 
 int OPENSSL_INIT_LOAD_SSL_STRINGS ; 
 int OPENSSL_INIT_NO_LOAD_CONFIG ; 
 int OPENSSL_INIT_NO_LOAD_SSL_STRINGS ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUN_ONCE_ALT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_F_OPENSSL_INIT_SSL ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_init_load_ssl_strings ; 
 int /*<<< orphan*/  ossl_init_no_load_ssl_strings ; 
 int /*<<< orphan*/  ossl_init_ssl_base ; 
 int /*<<< orphan*/  ssl_base ; 
 int /*<<< orphan*/  ssl_strings ; 
 scalar_t__ stopped ; 

int OPENSSL_init_ssl(uint64_t opts, const OPENSSL_INIT_SETTINGS * settings)
{
    static int stoperrset = 0;

    if (stopped) {
        if (!stoperrset) {
            /*
             * We only ever set this once to avoid getting into an infinite
             * loop where the error system keeps trying to init and fails so
             * sets an error etc
             */
            stoperrset = 1;
            SSLerr(SSL_F_OPENSSL_INIT_SSL, ERR_R_INIT_FAIL);
        }
        return 0;
    }

    opts |= OPENSSL_INIT_ADD_ALL_CIPHERS
         |  OPENSSL_INIT_ADD_ALL_DIGESTS;
#ifndef OPENSSL_NO_AUTOLOAD_CONFIG
    if ((opts & OPENSSL_INIT_NO_LOAD_CONFIG) == 0)
        opts |= OPENSSL_INIT_LOAD_CONFIG;
#endif

    if (!OPENSSL_init_crypto(opts, settings))
        return 0;

    if (!RUN_ONCE(&ssl_base, ossl_init_ssl_base))
        return 0;

    if ((opts & OPENSSL_INIT_NO_LOAD_SSL_STRINGS)
        && !RUN_ONCE_ALT(&ssl_strings, ossl_init_no_load_ssl_strings,
                         ossl_init_load_ssl_strings))
        return 0;

    if ((opts & OPENSSL_INIT_LOAD_SSL_STRINGS)
        && !RUN_ONCE(&ssl_strings, ossl_init_load_ssl_strings))
        return 0;

    return 1;
}
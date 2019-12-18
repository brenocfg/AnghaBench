#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sane; int /*<<< orphan*/  value; } ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  (* handler ) () ;} ;
typedef  TYPE_1__ OPENSSL_INIT_STOP ;
typedef  int /*<<< orphan*/  CRYPTO_THREAD_LOCAL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_cleanup_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_secure_malloc_done () ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  async_deinit () ; 
 scalar_t__ async_inited ; 
 scalar_t__ base_inited ; 
 int /*<<< orphan*/  bio_cleanup () ; 
 int /*<<< orphan*/  comp_zlib_cleanup_int () ; 
 int /*<<< orphan*/  conf_modules_free_int () ; 
 int /*<<< orphan*/  crypto_cleanup_all_ex_data_int () ; 
 TYPE_3__ destructor_key ; 
 int /*<<< orphan*/  engine_cleanup_int () ; 
 int /*<<< orphan*/  err_cleanup () ; 
 int /*<<< orphan*/  err_free_strings_int () ; 
 int /*<<< orphan*/  evp_cleanup_int () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * init_lock ; 
 scalar_t__ load_crypto_strings_inited ; 
 int /*<<< orphan*/  obj_cleanup_int () ; 
 int /*<<< orphan*/  ossl_init_get_thread_local (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_init_thread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_store_cleanup_int () ; 
 int /*<<< orphan*/  rand_cleanup_int () ; 
 int /*<<< orphan*/  rand_drbg_cleanup_int () ; 
 int /*<<< orphan*/  stderr ; 
 TYPE_1__* stop_handlers ; 
 int stopped ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ zlib_inited ; 

void OPENSSL_cleanup(void)
{
    OPENSSL_INIT_STOP *currhandler, *lasthandler;
    CRYPTO_THREAD_LOCAL key;

    /* If we've not been inited then no need to deinit */
    if (!base_inited)
        return;

    /* Might be explicitly called and also by atexit */
    if (stopped)
        return;
    stopped = 1;

    /*
     * Thread stop may not get automatically called by the thread library for
     * the very last thread in some situations, so call it directly.
     */
    ossl_init_thread_stop(ossl_init_get_thread_local(0));

    currhandler = stop_handlers;
    while (currhandler != NULL) {
        currhandler->handler();
        lasthandler = currhandler;
        currhandler = currhandler->next;
        OPENSSL_free(lasthandler);
    }
    stop_handlers = NULL;

    CRYPTO_THREAD_lock_free(init_lock);
    init_lock = NULL;

    /*
     * We assume we are single-threaded for this function, i.e. no race
     * conditions for the various "*_inited" vars below.
     */

#ifndef OPENSSL_NO_COMP
    if (zlib_inited) {
#ifdef OPENSSL_INIT_DEBUG
        fprintf(stderr, "OPENSSL_INIT: OPENSSL_cleanup: "
                        "comp_zlib_cleanup_int()\n");
#endif
        comp_zlib_cleanup_int();
    }
#endif

    if (async_inited) {
# ifdef OPENSSL_INIT_DEBUG
        fprintf(stderr, "OPENSSL_INIT: OPENSSL_cleanup: "
                        "async_deinit()\n");
# endif
        async_deinit();
    }

    if (load_crypto_strings_inited) {
#ifdef OPENSSL_INIT_DEBUG
        fprintf(stderr, "OPENSSL_INIT: OPENSSL_cleanup: "
                        "err_free_strings_int()\n");
#endif
        err_free_strings_int();
    }

    key = destructor_key.value;
    destructor_key.sane = -1;
    CRYPTO_THREAD_cleanup_local(&key);

#ifdef OPENSSL_INIT_DEBUG
    fprintf(stderr, "OPENSSL_INIT: OPENSSL_cleanup: "
                    "rand_cleanup_int()\n");
    fprintf(stderr, "OPENSSL_INIT: OPENSSL_cleanup: "
                    "conf_modules_free_int()\n");
#ifndef OPENSSL_NO_ENGINE
    fprintf(stderr, "OPENSSL_INIT: OPENSSL_cleanup: "
                    "engine_cleanup_int()\n");
#endif
    fprintf(stderr, "OPENSSL_INIT: OPENSSL_cleanup: "
                    "crypto_cleanup_all_ex_data_int()\n");
    fprintf(stderr, "OPENSSL_INIT: OPENSSL_cleanup: "
                    "bio_sock_cleanup_int()\n");
    fprintf(stderr, "OPENSSL_INIT: OPENSSL_cleanup: "
                    "bio_cleanup()\n");
    fprintf(stderr, "OPENSSL_INIT: OPENSSL_cleanup: "
                    "evp_cleanup_int()\n");
    fprintf(stderr, "OPENSSL_INIT: OPENSSL_cleanup: "
                    "obj_cleanup_int()\n");
    fprintf(stderr, "OPENSSL_INIT: OPENSSL_cleanup: "
                    "err_cleanup()\n");
#endif
    /*
     * Note that cleanup order is important:
     * - rand_cleanup_int could call an ENGINE's RAND cleanup function so
     * must be called before engine_cleanup_int()
     * - ENGINEs use CRYPTO_EX_DATA and therefore, must be cleaned up
     * before the ex data handlers are wiped in CRYPTO_cleanup_all_ex_data().
     * - conf_modules_free_int() can end up in ENGINE code so must be called
     * before engine_cleanup_int()
     * - ENGINEs and additional EVP algorithms might use added OIDs names so
     * obj_cleanup_int() must be called last
     */
    rand_cleanup_int();
    rand_drbg_cleanup_int();
    conf_modules_free_int();
#ifndef OPENSSL_NO_ENGINE
    engine_cleanup_int();
#endif
    ossl_store_cleanup_int();
    crypto_cleanup_all_ex_data_int();
    bio_cleanup();
    evp_cleanup_int();
    obj_cleanup_int();
    err_cleanup();

    CRYPTO_secure_malloc_done();

    base_inited = 0;
}
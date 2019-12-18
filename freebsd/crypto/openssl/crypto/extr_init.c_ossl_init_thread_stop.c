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
struct thread_local_inits_st {scalar_t__ rand; scalar_t__ err_state; scalar_t__ async; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (struct thread_local_inits_st*) ; 
 int /*<<< orphan*/  async_delete_thread_state () ; 
 int /*<<< orphan*/  drbg_delete_thread_state () ; 
 int /*<<< orphan*/  err_delete_thread_state () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void ossl_init_thread_stop(struct thread_local_inits_st *locals)
{
    /* Can't do much about this */
    if (locals == NULL)
        return;

    if (locals->async) {
#ifdef OPENSSL_INIT_DEBUG
        fprintf(stderr, "OPENSSL_INIT: ossl_init_thread_stop: "
                        "async_delete_thread_state()\n");
#endif
        async_delete_thread_state();
    }

    if (locals->err_state) {
#ifdef OPENSSL_INIT_DEBUG
        fprintf(stderr, "OPENSSL_INIT: ossl_init_thread_stop: "
                        "err_delete_thread_state()\n");
#endif
        err_delete_thread_state();
    }

    if (locals->rand) {
#ifdef OPENSSL_INIT_DEBUG
        fprintf(stderr, "OPENSSL_INIT: ossl_init_thread_stop: "
                        "drbg_delete_thread_state()\n");
#endif
        drbg_delete_thread_state();
    }

    OPENSSL_free(locals);
}
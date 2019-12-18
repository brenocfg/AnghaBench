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
struct TYPE_5__ {char const* scheme; int /*<<< orphan*/ * close; int /*<<< orphan*/ * eof; int /*<<< orphan*/ * load; int /*<<< orphan*/ * open; } ;
typedef  TYPE_1__ OSSL_STORE_LOADER ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*) ; 
 int /*<<< orphan*/  OSSL_STORE_F_OSSL_STORE_UNREGISTER_LOADER_INT ; 
 int /*<<< orphan*/  OSSL_STORE_R_UNREGISTERED_SCHEME ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_registry_init ; 
 TYPE_1__* lh_OSSL_STORE_LOADER_delete (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  loader_register ; 
 int /*<<< orphan*/  registry_init ; 
 int /*<<< orphan*/  registry_lock ; 

OSSL_STORE_LOADER *ossl_store_unregister_loader_int(const char *scheme)
{
    OSSL_STORE_LOADER template;
    OSSL_STORE_LOADER *loader = NULL;

    template.scheme = scheme;
    template.open = NULL;
    template.load = NULL;
    template.eof = NULL;
    template.close = NULL;

    if (!RUN_ONCE(&registry_init, do_registry_init)) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_UNREGISTER_LOADER_INT,
                      ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    CRYPTO_THREAD_write_lock(registry_lock);

    loader = lh_OSSL_STORE_LOADER_delete(loader_register, &template);

    if (loader == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_UNREGISTER_LOADER_INT,
                      OSSL_STORE_R_UNREGISTERED_SCHEME);
        ERR_add_error_data(2, "scheme=", scheme);
    }

    CRYPTO_THREAD_unlock(registry_lock);

    return loader;
}
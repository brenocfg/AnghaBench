#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* scheme; int /*<<< orphan*/ * close; int /*<<< orphan*/ * error; int /*<<< orphan*/ * eof; int /*<<< orphan*/ * load; int /*<<< orphan*/ * open; } ;
typedef  TYPE_1__ OSSL_STORE_LOADER ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char*) ; 
 int /*<<< orphan*/  OSSL_STORE_F_OSSL_STORE_REGISTER_LOADER_INT ; 
 int /*<<< orphan*/  OSSL_STORE_R_INVALID_SCHEME ; 
 int /*<<< orphan*/  OSSL_STORE_R_LOADER_INCOMPLETE ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_registry_init ; 
 scalar_t__ lh_OSSL_STORE_LOADER_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lh_OSSL_STORE_LOADER_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * lh_OSSL_STORE_LOADER_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * loader_register ; 
 scalar_t__ ossl_isalpha (char const) ; 
 scalar_t__ ossl_isdigit (char const) ; 
 int /*<<< orphan*/  registry_init ; 
 int /*<<< orphan*/  registry_lock ; 
 int /*<<< orphan*/  store_loader_cmp ; 
 int /*<<< orphan*/  store_loader_hash ; 
 int /*<<< orphan*/ * strchr (char*,char const) ; 

int ossl_store_register_loader_int(OSSL_STORE_LOADER *loader)
{
    const char *scheme = loader->scheme;
    int ok = 0;

    /*
     * Check that the given scheme conforms to correct scheme syntax as per
     * RFC 3986:
     *
     * scheme        = ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
     */
    if (ossl_isalpha(*scheme))
        while (*scheme != '\0'
               && (ossl_isalpha(*scheme)
                   || ossl_isdigit(*scheme)
                   || strchr("+-.", *scheme) != NULL))
            scheme++;
    if (*scheme != '\0') {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_REGISTER_LOADER_INT,
                      OSSL_STORE_R_INVALID_SCHEME);
        ERR_add_error_data(2, "scheme=", loader->scheme);
        return 0;
    }

    /* Check that functions we absolutely require are present */
    if (loader->open == NULL || loader->load == NULL || loader->eof == NULL
        || loader->error == NULL || loader->close == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_REGISTER_LOADER_INT,
                      OSSL_STORE_R_LOADER_INCOMPLETE);
        return 0;
    }

    if (!RUN_ONCE(&registry_init, do_registry_init)) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_REGISTER_LOADER_INT,
                      ERR_R_MALLOC_FAILURE);
        return 0;
    }
    CRYPTO_THREAD_write_lock(registry_lock);

    if (loader_register == NULL) {
        loader_register = lh_OSSL_STORE_LOADER_new(store_loader_hash,
                                                   store_loader_cmp);
    }

    if (loader_register != NULL
        && (lh_OSSL_STORE_LOADER_insert(loader_register, loader) != NULL
            || lh_OSSL_STORE_LOADER_error(loader_register) == 0))
        ok = 1;

    CRYPTO_THREAD_unlock(registry_lock);

    return ok;
}
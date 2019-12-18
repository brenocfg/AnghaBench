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
struct TYPE_4__ {char const* scheme; int /*<<< orphan*/ * engine; } ;
typedef  TYPE_1__ OSSL_STORE_LOADER ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  OSSL_STORE_F_OSSL_STORE_LOADER_NEW ; 
 int /*<<< orphan*/  OSSL_STORE_R_INVALID_SCHEME ; 
 int /*<<< orphan*/  OSSL_STOREerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

OSSL_STORE_LOADER *OSSL_STORE_LOADER_new(ENGINE *e, const char *scheme)
{
    OSSL_STORE_LOADER *res = NULL;

    /*
     * We usually don't check NULL arguments.  For loaders, though, the
     * scheme is crucial and must never be NULL, or the user will get
     * mysterious errors when trying to register the created loader
     * later on.
     */
    if (scheme == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_LOADER_NEW,
                      OSSL_STORE_R_INVALID_SCHEME);
        return NULL;
    }

    if ((res = OPENSSL_zalloc(sizeof(*res))) == NULL) {
        OSSL_STOREerr(OSSL_STORE_F_OSSL_STORE_LOADER_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    res->engine = e;
    res->scheme = scheme;
    return res;
}
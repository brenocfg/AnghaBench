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
typedef  int /*<<< orphan*/  X509_STORE ;
typedef  int /*<<< orphan*/  X509_LOOKUP ;

/* Variables and functions */
 int /*<<< orphan*/  X509_FILETYPE_PEM ; 
 int /*<<< orphan*/  X509_LOOKUP_file () ; 
 int X509_LOOKUP_load_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_STORE_add_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_STORE_new () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  stderr ; 

X509_STORE * openssl_init_cert_store(char const * crt_file)
{
    int ret = 0;
    X509_STORE *store = X509_STORE_new();

    if (store != NULL) {
        X509_LOOKUP *lookup = X509_STORE_add_lookup(store, X509_LOOKUP_file());
        ret = X509_LOOKUP_load_file(lookup, crt_file, X509_FILETYPE_PEM);
        if (ret != 1) {
            fprintf(stderr, "Cannot load store (%s), ret = %d\n",
                crt_file, ret);
        }
    }

    return store;
}
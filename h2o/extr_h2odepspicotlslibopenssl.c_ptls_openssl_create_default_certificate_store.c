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
 int /*<<< orphan*/  X509_FILETYPE_DEFAULT ; 
 int /*<<< orphan*/  X509_LOOKUP_add_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_LOOKUP_file () ; 
 int /*<<< orphan*/  X509_LOOKUP_hash_dir () ; 
 int /*<<< orphan*/  X509_LOOKUP_load_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_STORE_add_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_STORE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_STORE_new () ; 

X509_STORE *ptls_openssl_create_default_certificate_store(void)
{
    X509_STORE *store;
    X509_LOOKUP *lookup;

    if ((store = X509_STORE_new()) == NULL)
        goto Error;
    if ((lookup = X509_STORE_add_lookup(store, X509_LOOKUP_file())) == NULL)
        goto Error;
    X509_LOOKUP_load_file(lookup, NULL, X509_FILETYPE_DEFAULT);
    if ((lookup = X509_STORE_add_lookup(store, X509_LOOKUP_hash_dir())) == NULL)
        goto Error;
    X509_LOOKUP_add_dir(lookup, NULL, X509_FILETYPE_DEFAULT);

    return store;
Error:
    if (store != NULL)
        X509_STORE_free(store);
    return NULL;
}
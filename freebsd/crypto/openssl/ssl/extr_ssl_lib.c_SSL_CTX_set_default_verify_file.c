#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_LOOKUP ;
struct TYPE_3__ {int /*<<< orphan*/  cert_store; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  X509_FILETYPE_DEFAULT ; 
 int /*<<< orphan*/  X509_LOOKUP_file () ; 
 int /*<<< orphan*/  X509_LOOKUP_load_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_STORE_add_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int SSL_CTX_set_default_verify_file(SSL_CTX *ctx)
{
    X509_LOOKUP *lookup;

    lookup = X509_STORE_add_lookup(ctx->cert_store, X509_LOOKUP_file());
    if (lookup == NULL)
        return 0;

    X509_LOOKUP_load_file(lookup, NULL, X509_FILETYPE_DEFAULT);

    /* Clear any errors if the default file does not exist */
    ERR_clear_error();

    return 1;
}
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
typedef  int /*<<< orphan*/  EVP_PKEY_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_F_EVP_PKEY_METH_ADD0 ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * app_pkey_methods ; 
 int /*<<< orphan*/  pmeth_cmp ; 
 int /*<<< orphan*/ * sk_EVP_PKEY_METHOD_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_EVP_PKEY_METHOD_push (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sk_EVP_PKEY_METHOD_sort (int /*<<< orphan*/ *) ; 

int EVP_PKEY_meth_add0(const EVP_PKEY_METHOD *pmeth)
{
    if (app_pkey_methods == NULL) {
        app_pkey_methods = sk_EVP_PKEY_METHOD_new(pmeth_cmp);
        if (app_pkey_methods == NULL){
            EVPerr(EVP_F_EVP_PKEY_METH_ADD0, ERR_R_MALLOC_FAILURE);
            return 0;
        }
    }
    if (!sk_EVP_PKEY_METHOD_push(app_pkey_methods, pmeth)) {
        EVPerr(EVP_F_EVP_PKEY_METH_ADD0, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    sk_EVP_PKEY_METHOD_sort(app_pkey_methods);
    return 1;
}
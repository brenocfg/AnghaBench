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
 int /*<<< orphan*/  app_pkey_methods ; 
 int /*<<< orphan*/ * sk_EVP_PKEY_METHOD_delete_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int EVP_PKEY_meth_remove(const EVP_PKEY_METHOD *pmeth)
{
    const EVP_PKEY_METHOD *ret;

    ret = sk_EVP_PKEY_METHOD_delete_ptr(app_pkey_methods, pmeth);

    return ret == NULL ? 0 : 1;
}
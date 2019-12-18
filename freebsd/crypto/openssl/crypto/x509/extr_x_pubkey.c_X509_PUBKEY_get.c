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
typedef  int /*<<< orphan*/  X509_PUBKEY ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_up_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_PUBKEY_get0 (int /*<<< orphan*/ *) ; 

EVP_PKEY *X509_PUBKEY_get(X509_PUBKEY *key)
{
    EVP_PKEY *ret = X509_PUBKEY_get0(key);
    if (ret != NULL)
        EVP_PKEY_up_ref(ret);
    return ret;
}
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
typedef  int /*<<< orphan*/  EVP_PKEY_ASN1_METHOD ;

/* Variables and functions */
 int OSSL_NELEM (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  app_methods ; 
 int /*<<< orphan*/  const* sk_EVP_PKEY_ASN1_METHOD_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  const** standard_methods ; 

const EVP_PKEY_ASN1_METHOD *EVP_PKEY_asn1_get0(int idx)
{
    int num = OSSL_NELEM(standard_methods);
    if (idx < 0)
        return NULL;
    if (idx < num)
        return standard_methods[idx];
    idx -= num;
    return sk_EVP_PKEY_ASN1_METHOD_value(app_methods, idx);
}
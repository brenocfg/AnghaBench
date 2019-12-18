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

/* Variables and functions */
 int OSSL_NELEM (int /*<<< orphan*/ ) ; 
 scalar_t__ app_methods ; 
 scalar_t__ sk_EVP_PKEY_ASN1_METHOD_num (scalar_t__) ; 
 int /*<<< orphan*/  standard_methods ; 

int EVP_PKEY_asn1_get_count(void)
{
    int num = OSSL_NELEM(standard_methods);
    if (app_methods)
        num += sk_EVP_PKEY_ASN1_METHOD_num(app_methods);
    return num;
}
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
typedef  int /*<<< orphan*/  X509_CRL_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  const* default_crl_method ; 
 int /*<<< orphan*/  int_crl_meth ; 

void X509_CRL_set_default_method(const X509_CRL_METHOD *meth)
{
    if (meth == NULL)
        default_crl_method = &int_crl_meth;
    else
        default_crl_method = meth;
}
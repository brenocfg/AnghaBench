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
 int /*<<< orphan*/  X509_PUBKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_PUBKEY_set (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int i2d_X509_PUBKEY (int /*<<< orphan*/ *,unsigned char**) ; 

int i2d_PUBKEY(EVP_PKEY *a, unsigned char **pp)
{
    X509_PUBKEY *xpk = NULL;
    int ret;
    if (!a)
        return 0;
    if (!X509_PUBKEY_set(&xpk, a))
        return -1;
    ret = i2d_X509_PUBKEY(xpk, pp);
    X509_PUBKEY_free(xpk);
    return ret;
}
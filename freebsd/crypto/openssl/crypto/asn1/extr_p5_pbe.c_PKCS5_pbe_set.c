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
typedef  int /*<<< orphan*/  X509_ALGOR ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_PKCS5_PBE_SET ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ PKCS5_pbe_set0_algor (int /*<<< orphan*/ *,int,int,unsigned char const*,int) ; 
 int /*<<< orphan*/  X509_ALGOR_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_ALGOR_new () ; 

X509_ALGOR *PKCS5_pbe_set(int alg, int iter,
                          const unsigned char *salt, int saltlen)
{
    X509_ALGOR *ret;
    ret = X509_ALGOR_new();
    if (ret == NULL) {
        ASN1err(ASN1_F_PKCS5_PBE_SET, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    if (PKCS5_pbe_set0_algor(ret, alg, iter, salt, saltlen))
        return ret;

    X509_ALGOR_free(ret);
    return NULL;
}
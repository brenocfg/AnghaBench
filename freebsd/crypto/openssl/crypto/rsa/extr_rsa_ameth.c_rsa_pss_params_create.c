#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  maskHash; int /*<<< orphan*/  maskGenAlgorithm; int /*<<< orphan*/  hashAlgorithm; int /*<<< orphan*/ * saltLength; } ;
typedef  TYPE_1__ RSA_PSS_PARAMS ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_INTEGER_new () ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RSA_PSS_PARAMS_free (TYPE_1__*) ; 
 TYPE_1__* RSA_PSS_PARAMS_new () ; 
 int /*<<< orphan*/  rsa_md_to_algor (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  rsa_md_to_mgf1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

RSA_PSS_PARAMS *rsa_pss_params_create(const EVP_MD *sigmd,
                                      const EVP_MD *mgf1md, int saltlen)
{
    RSA_PSS_PARAMS *pss = RSA_PSS_PARAMS_new();

    if (pss == NULL)
        goto err;
    if (saltlen != 20) {
        pss->saltLength = ASN1_INTEGER_new();
        if (pss->saltLength == NULL)
            goto err;
        if (!ASN1_INTEGER_set(pss->saltLength, saltlen))
            goto err;
    }
    if (!rsa_md_to_algor(&pss->hashAlgorithm, sigmd))
        goto err;
    if (mgf1md == NULL)
        mgf1md = sigmd;
    if (!rsa_md_to_mgf1(&pss->maskGenAlgorithm, mgf1md))
        goto err;
    if (!rsa_md_to_algor(&pss->maskHash, mgf1md))
        goto err;
    return pss;
 err:
    RSA_PSS_PARAMS_free(pss);
    return NULL;
}
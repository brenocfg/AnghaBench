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
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_PKEY_CTRL_DEFAULT_MD_NID ; 
 int evp_pkey_asn1_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int EVP_PKEY_get_default_digest_nid(EVP_PKEY *pkey, int *pnid)
{
    return evp_pkey_asn1_ctrl(pkey, ASN1_PKEY_CTRL_DEFAULT_MD_NID, 0, pnid);
}
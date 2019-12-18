#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ EVP_MD ;

/* Variables and functions */
 int EVP_MD_FLAG_DIGALGID_ABSENT ; 
 int /*<<< orphan*/  EVP_MD_type (TYPE_1__ const*) ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int V_ASN1_NULL ; 
 int V_ASN1_UNDEF ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void X509_ALGOR_set_md(X509_ALGOR *alg, const EVP_MD *md)
{
    int param_type;

    if (md->flags & EVP_MD_FLAG_DIGALGID_ABSENT)
        param_type = V_ASN1_UNDEF;
    else
        param_type = V_ASN1_NULL;

    X509_ALGOR_set0(alg, OBJ_nid2obj(EVP_MD_type(md)), param_type, NULL);

}
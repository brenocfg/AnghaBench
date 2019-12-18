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
 int ASN1_PKEY_DYNAMIC ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * EVP_PKEY_meth_get0 (size_t) ; 
 int /*<<< orphan*/  EVP_PKEY_meth_get0_info (int*,int*,int /*<<< orphan*/  const*) ; 
 size_t EVP_PKEY_meth_get_count () ; 
 char* OBJ_nid2ln (int) ; 
 int /*<<< orphan*/  bio_out ; 

__attribute__((used)) static void list_pkey_meth(void)
{
    size_t i;
    size_t meth_count = EVP_PKEY_meth_get_count();

    for (i = 0; i < meth_count; i++) {
        const EVP_PKEY_METHOD *pmeth = EVP_PKEY_meth_get0(i);
        int pkey_id, pkey_flags;

        EVP_PKEY_meth_get0_info(&pkey_id, &pkey_flags, pmeth);
        BIO_printf(bio_out, "%s\n", OBJ_nid2ln(pkey_id));
        BIO_printf(bio_out, "\tType: %s Algorithm\n",
                   pkey_flags & ASN1_PKEY_DYNAMIC ?  "External" : "Builtin");
    }
}
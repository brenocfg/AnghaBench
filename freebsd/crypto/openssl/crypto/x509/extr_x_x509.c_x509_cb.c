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
struct TYPE_4__ {int ex_pathlen; int ex_pcpathlen; int /*<<< orphan*/ * rfc3779_asid; int /*<<< orphan*/ * rfc3779_addr; int /*<<< orphan*/ * nc; int /*<<< orphan*/ * altname; int /*<<< orphan*/ * policy_cache; int /*<<< orphan*/ * crldp; int /*<<< orphan*/ * akid; int /*<<< orphan*/ * skid; int /*<<< orphan*/ * aux; int /*<<< orphan*/  ex_data; int /*<<< orphan*/  ex_flags; int /*<<< orphan*/  ex_nscert; int /*<<< orphan*/  ex_xkusage; int /*<<< orphan*/  ex_kusage; int /*<<< orphan*/  ex_cached; } ;
typedef  TYPE_1__ X509 ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASIdentifiers_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (int /*<<< orphan*/ *) ; 
#define  ASN1_OP_D2I_PRE 130 
#define  ASN1_OP_FREE_POST 129 
#define  ASN1_OP_NEW_POST 128 
 int /*<<< orphan*/  AUTHORITY_KEYID_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRL_DIST_POINTS_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_EX_INDEX_X509 ; 
 int /*<<< orphan*/  CRYPTO_free_ex_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_new_ex_data (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERAL_NAMES_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPAddressFamily_free ; 
 int /*<<< orphan*/  NAME_CONSTRAINTS_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_CERT_AUX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  policy_cache_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_IPAddressFamily_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x509_cb(int operation, ASN1_VALUE **pval, const ASN1_ITEM *it,
                   void *exarg)
{
    X509 *ret = (X509 *)*pval;

    switch (operation) {

    case ASN1_OP_D2I_PRE:
        CRYPTO_free_ex_data(CRYPTO_EX_INDEX_X509, ret, &ret->ex_data);
        X509_CERT_AUX_free(ret->aux);
        ASN1_OCTET_STRING_free(ret->skid);
        AUTHORITY_KEYID_free(ret->akid);
        CRL_DIST_POINTS_free(ret->crldp);
        policy_cache_free(ret->policy_cache);
        GENERAL_NAMES_free(ret->altname);
        NAME_CONSTRAINTS_free(ret->nc);
#ifndef OPENSSL_NO_RFC3779
        sk_IPAddressFamily_pop_free(ret->rfc3779_addr, IPAddressFamily_free);
        ASIdentifiers_free(ret->rfc3779_asid);
#endif

        /* fall thru */

    case ASN1_OP_NEW_POST:
        ret->ex_cached = 0;
        ret->ex_kusage = 0;
        ret->ex_xkusage = 0;
        ret->ex_nscert = 0;
        ret->ex_flags = 0;
        ret->ex_pathlen = -1;
        ret->ex_pcpathlen = -1;
        ret->skid = NULL;
        ret->akid = NULL;
        ret->policy_cache = NULL;
        ret->altname = NULL;
        ret->nc = NULL;
#ifndef OPENSSL_NO_RFC3779
        ret->rfc3779_addr = NULL;
        ret->rfc3779_asid = NULL;
#endif
        ret->aux = NULL;
        ret->crldp = NULL;
        if (!CRYPTO_new_ex_data(CRYPTO_EX_INDEX_X509, ret, &ret->ex_data))
            return 0;
        break;

    case ASN1_OP_FREE_POST:
        CRYPTO_free_ex_data(CRYPTO_EX_INDEX_X509, ret, &ret->ex_data);
        X509_CERT_AUX_free(ret->aux);
        ASN1_OCTET_STRING_free(ret->skid);
        AUTHORITY_KEYID_free(ret->akid);
        CRL_DIST_POINTS_free(ret->crldp);
        policy_cache_free(ret->policy_cache);
        GENERAL_NAMES_free(ret->altname);
        NAME_CONSTRAINTS_free(ret->nc);
#ifndef OPENSSL_NO_RFC3779
        sk_IPAddressFamily_pop_free(ret->rfc3779_addr, IPAddressFamily_free);
        ASIdentifiers_free(ret->rfc3779_asid);
#endif
        break;

    }

    return 1;

}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  X509_EXTENSION ;
struct TYPE_14__ {TYPE_2__* location; int /*<<< orphan*/ * method; } ;
struct TYPE_13__ {int /*<<< orphan*/ * locator; int /*<<< orphan*/ * issuer; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ia5; } ;
struct TYPE_12__ {TYPE_1__ d; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ OCSP_SERVICELOC ;
typedef  int /*<<< orphan*/  ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_IA5STRING ;
typedef  TYPE_4__ ACCESS_DESCRIPTION ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_DESCRIPTION_free (TYPE_4__*) ; 
 TYPE_4__* ACCESS_DESCRIPTION_new () ; 
 int /*<<< orphan*/  ASN1_IA5STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_IA5STRING_new () ; 
 int /*<<< orphan*/  ASN1_STRING_set (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  GEN_URI ; 
 int /*<<< orphan*/  NID_ad_OCSP ; 
 int /*<<< orphan*/  NID_id_pkix_OCSP_serviceLocator ; 
 int /*<<< orphan*/ * OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCSP_SERVICELOC_free (TYPE_3__*) ; 
 TYPE_3__* OCSP_SERVICELOC_new () ; 
 int /*<<< orphan*/ * X509V3_EXT_i2d (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * X509_NAME_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_NAME_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_ACCESS_DESCRIPTION_new_null () ; 
 int /*<<< orphan*/  sk_ACCESS_DESCRIPTION_push (int /*<<< orphan*/ *,TYPE_4__*) ; 

X509_EXTENSION *OCSP_url_svcloc_new(X509_NAME *issuer, const char **urls)
{
    X509_EXTENSION *x = NULL;
    ASN1_IA5STRING *ia5 = NULL;
    OCSP_SERVICELOC *sloc = NULL;
    ACCESS_DESCRIPTION *ad = NULL;

    if ((sloc = OCSP_SERVICELOC_new()) == NULL)
        goto err;
    X509_NAME_free(sloc->issuer);
    if ((sloc->issuer = X509_NAME_dup(issuer)) == NULL)
        goto err;
    if (urls && *urls
        && (sloc->locator = sk_ACCESS_DESCRIPTION_new_null()) == NULL)
        goto err;
    while (urls && *urls) {
        if ((ad = ACCESS_DESCRIPTION_new()) == NULL)
            goto err;
        if ((ad->method = OBJ_nid2obj(NID_ad_OCSP)) == NULL)
            goto err;
        if ((ia5 = ASN1_IA5STRING_new()) == NULL)
            goto err;
        if (!ASN1_STRING_set((ASN1_STRING *)ia5, *urls, -1))
            goto err;
        /* ad->location is allocated inside ACCESS_DESCRIPTION_new */
        ad->location->type = GEN_URI;
        ad->location->d.ia5 = ia5;
        ia5 = NULL;
        if (!sk_ACCESS_DESCRIPTION_push(sloc->locator, ad))
            goto err;
        ad = NULL;
        urls++;
    }
    x = X509V3_EXT_i2d(NID_id_pkix_OCSP_serviceLocator, 0, sloc);
 err:
    ASN1_IA5STRING_free(ia5);
    ACCESS_DESCRIPTION_free(ad);
    OCSP_SERVICELOC_free(sloc);
    return x;
}
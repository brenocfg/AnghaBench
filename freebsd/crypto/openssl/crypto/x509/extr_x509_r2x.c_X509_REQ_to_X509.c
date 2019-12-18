#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  attributes; } ;
struct TYPE_18__ {TYPE_1__ req_info; } ;
typedef  TYPE_3__ X509_REQ ;
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_17__ {int /*<<< orphan*/  notAfter; int /*<<< orphan*/  notBefore; } ;
struct TYPE_19__ {TYPE_2__ validity; int /*<<< orphan*/ * version; } ;
typedef  TYPE_4__ X509_CINF ;
struct TYPE_20__ {TYPE_4__ cert_info; } ;
typedef  TYPE_5__ X509 ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_INTEGER_new () ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_md5 () ; 
 int /*<<< orphan*/  X509_F_X509_REQ_TO_X509 ; 
 int /*<<< orphan*/ * X509_REQ_get0_pubkey (TYPE_3__*) ; 
 int /*<<< orphan*/ * X509_REQ_get_subject_name (TYPE_3__*) ; 
 int /*<<< orphan*/  X509_free (TYPE_5__*) ; 
 int /*<<< orphan*/ * X509_gmtime_adj (int /*<<< orphan*/ ,long) ; 
 TYPE_5__* X509_new () ; 
 scalar_t__ X509_set_issuer_name (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_set_pubkey (TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ X509_set_subject_name (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_sign (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sk_X509_ATTRIBUTE_num (int /*<<< orphan*/ ) ; 

X509 *X509_REQ_to_X509(X509_REQ *r, int days, EVP_PKEY *pkey)
{
    X509 *ret = NULL;
    X509_CINF *xi = NULL;
    X509_NAME *xn;
    EVP_PKEY *pubkey = NULL;

    if ((ret = X509_new()) == NULL) {
        X509err(X509_F_X509_REQ_TO_X509, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    /* duplicate the request */
    xi = &ret->cert_info;

    if (sk_X509_ATTRIBUTE_num(r->req_info.attributes) != 0) {
        if ((xi->version = ASN1_INTEGER_new()) == NULL)
            goto err;
        if (!ASN1_INTEGER_set(xi->version, 2))
            goto err;
/*-     xi->extensions=ri->attributes; <- bad, should not ever be done
        ri->attributes=NULL; */
    }

    xn = X509_REQ_get_subject_name(r);
    if (X509_set_subject_name(ret, xn) == 0)
        goto err;
    if (X509_set_issuer_name(ret, xn) == 0)
        goto err;

    if (X509_gmtime_adj(xi->validity.notBefore, 0) == NULL)
        goto err;
    if (X509_gmtime_adj(xi->validity.notAfter, (long)60 * 60 * 24 * days) ==
        NULL)
        goto err;

    pubkey = X509_REQ_get0_pubkey(r);
    if (pubkey == NULL || !X509_set_pubkey(ret, pubkey))
        goto err;

    if (!X509_sign(ret, pkey, EVP_md5()))
        goto err;
    return ret;

 err:
    X509_free(ret);
    return NULL;
}
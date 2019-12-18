#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_REVOKED ;
struct TYPE_5__ {int modified; } ;
struct TYPE_6__ {TYPE_1__ enc; int /*<<< orphan*/ * revoked; } ;
typedef  TYPE_2__ X509_CRL_INFO ;
struct TYPE_7__ {TYPE_2__ crl; } ;
typedef  TYPE_3__ X509_CRL ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_X509_CRL_ADD0_REVOKED ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  X509_REVOKED_cmp ; 
 int /*<<< orphan*/ * sk_X509_REVOKED_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_REVOKED_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int X509_CRL_add0_revoked(X509_CRL *crl, X509_REVOKED *rev)
{
    X509_CRL_INFO *inf;

    inf = &crl->crl;
    if (inf->revoked == NULL)
        inf->revoked = sk_X509_REVOKED_new(X509_REVOKED_cmp);
    if (inf->revoked == NULL || !sk_X509_REVOKED_push(inf->revoked, rev)) {
        ASN1err(ASN1_F_X509_CRL_ADD0_REVOKED, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    inf->enc.modified = 1;
    return 1;
}
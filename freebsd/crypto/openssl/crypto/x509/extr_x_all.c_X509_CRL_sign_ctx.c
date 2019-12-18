#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int modified; } ;
struct TYPE_7__ {int /*<<< orphan*/  sig_alg; TYPE_1__ enc; } ;
struct TYPE_6__ {TYPE_4__ crl; int /*<<< orphan*/  signature; int /*<<< orphan*/  sig_alg; } ;
typedef  TYPE_2__ X509_CRL ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_rptr (int /*<<< orphan*/ ) ; 
 int ASN1_item_sign_ctx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_CRL_INFO ; 

int X509_CRL_sign_ctx(X509_CRL *x, EVP_MD_CTX *ctx)
{
    x->crl.enc.modified = 1;
    return ASN1_item_sign_ctx(ASN1_ITEM_rptr(X509_CRL_INFO),
                              &x->crl.sig_alg, &x->sig_alg, &x->signature,
                              &x->crl, ctx);
}
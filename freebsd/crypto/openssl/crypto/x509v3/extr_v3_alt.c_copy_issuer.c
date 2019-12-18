#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_EXTENSION ;
struct TYPE_3__ {scalar_t__ flags; int /*<<< orphan*/  issuer_cert; } ;
typedef  TYPE_1__ X509V3_CTX ;
typedef  int /*<<< orphan*/  GENERAL_NAMES ;
typedef  int /*<<< orphan*/  GENERAL_NAME ;

/* Variables and functions */
 scalar_t__ CTX_TEST ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  NID_subject_alt_name ; 
 int /*<<< orphan*/ * X509V3_EXT_d2i (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509V3_F_COPY_ISSUER ; 
 int /*<<< orphan*/  X509V3_R_ISSUER_DECODE_ERROR ; 
 int /*<<< orphan*/  X509V3_R_NO_ISSUER_DETAILS ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_get_ext (int /*<<< orphan*/ ,int) ; 
 int X509_get_ext_by_NID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sk_GENERAL_NAME_free (int /*<<< orphan*/ *) ; 
 int sk_GENERAL_NAME_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_GENERAL_NAME_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_GENERAL_NAME_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sk_GENERAL_NAME_value (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int copy_issuer(X509V3_CTX *ctx, GENERAL_NAMES *gens)
{
    GENERAL_NAMES *ialt;
    GENERAL_NAME *gen;
    X509_EXTENSION *ext;
    int i, num;

    if (ctx && (ctx->flags == CTX_TEST))
        return 1;
    if (!ctx || !ctx->issuer_cert) {
        X509V3err(X509V3_F_COPY_ISSUER, X509V3_R_NO_ISSUER_DETAILS);
        goto err;
    }
    i = X509_get_ext_by_NID(ctx->issuer_cert, NID_subject_alt_name, -1);
    if (i < 0)
        return 1;
    if ((ext = X509_get_ext(ctx->issuer_cert, i)) == NULL
        || (ialt = X509V3_EXT_d2i(ext)) == NULL) {
        X509V3err(X509V3_F_COPY_ISSUER, X509V3_R_ISSUER_DECODE_ERROR);
        goto err;
    }

    num = sk_GENERAL_NAME_num(ialt);
    if (!sk_GENERAL_NAME_reserve(gens, num)) {
        X509V3err(X509V3_F_COPY_ISSUER, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    for (i = 0; i < num; i++) {
        gen = sk_GENERAL_NAME_value(ialt, i);
        sk_GENERAL_NAME_push(gens, gen);     /* no failure as it was reserved */
    }
    sk_GENERAL_NAME_free(ialt);

    return 1;

 err:
    return 0;

}
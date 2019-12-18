#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509V3_EXT_METHOD ;
struct TYPE_2__ {scalar_t__ crlTime; scalar_t__ crlNum; scalar_t__ crlUrl; } ;
typedef  TYPE_1__ OCSP_CRLID ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_GENERALIZEDTIME_print (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ASN1_STRING_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,int,char*) ; 
 scalar_t__ BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ i2a_ASN1_INTEGER (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int i2r_ocsp_crlid(const X509V3_EXT_METHOD *method, void *in, BIO *bp,
                          int ind)
{
    OCSP_CRLID *a = in;
    if (a->crlUrl) {
        if (BIO_printf(bp, "%*scrlUrl: ", ind, "") <= 0)
            goto err;
        if (!ASN1_STRING_print(bp, (ASN1_STRING *)a->crlUrl))
            goto err;
        if (BIO_write(bp, "\n", 1) <= 0)
            goto err;
    }
    if (a->crlNum) {
        if (BIO_printf(bp, "%*scrlNum: ", ind, "") <= 0)
            goto err;
        if (i2a_ASN1_INTEGER(bp, a->crlNum) <= 0)
            goto err;
        if (BIO_write(bp, "\n", 1) <= 0)
            goto err;
    }
    if (a->crlTime) {
        if (BIO_printf(bp, "%*scrlTime: ", ind, "") <= 0)
            goto err;
        if (!ASN1_GENERALIZEDTIME_print(bp, a->crlTime))
            goto err;
        if (BIO_write(bp, "\n", 1) <= 0)
            goto err;
    }
    return 1;
 err:
    return 0;
}
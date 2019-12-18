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
struct TYPE_4__ {unsigned char* data; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  DSA_SIG ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;
typedef  TYPE_1__ ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_PCTX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_bn_print (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  DSA_SIG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_SIG_get0 (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int X509_signature_dump (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/ * d2i_DSA_SIG (int /*<<< orphan*/ *,unsigned char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_sig_print(BIO *bp, const X509_ALGOR *sigalg,
                         const ASN1_STRING *sig, int indent, ASN1_PCTX *pctx)
{
    DSA_SIG *dsa_sig;
    const unsigned char *p;

    if (!sig) {
        if (BIO_puts(bp, "\n") <= 0)
            return 0;
        else
            return 1;
    }
    p = sig->data;
    dsa_sig = d2i_DSA_SIG(NULL, &p, sig->length);
    if (dsa_sig) {
        int rv = 0;
        const BIGNUM *r, *s;

        DSA_SIG_get0(dsa_sig, &r, &s);

        if (BIO_write(bp, "\n", 1) != 1)
            goto err;

        if (!ASN1_bn_print(bp, "r:   ", r, NULL, indent))
            goto err;
        if (!ASN1_bn_print(bp, "s:   ", s, NULL, indent))
            goto err;
        rv = 1;
 err:
        DSA_SIG_free(dsa_sig);
        return rv;
    }
    return X509_signature_dump(bp, sig, indent);
}
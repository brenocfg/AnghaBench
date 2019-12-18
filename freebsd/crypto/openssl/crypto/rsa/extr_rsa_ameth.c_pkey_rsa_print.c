#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* rsa; } ;
struct TYPE_11__ {TYPE_1__ pkey; } ;
struct TYPE_10__ {int /*<<< orphan*/  pss; int /*<<< orphan*/  prime_infos; int /*<<< orphan*/ * iqmp; int /*<<< orphan*/ * dmq1; int /*<<< orphan*/ * dmp1; int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; int /*<<< orphan*/ * d; int /*<<< orphan*/ * e; int /*<<< orphan*/ * n; } ;
struct TYPE_9__ {int /*<<< orphan*/ * t; int /*<<< orphan*/ * d; int /*<<< orphan*/ * r; } ;
typedef  TYPE_2__ RSA_PRIME_INFO ;
typedef  TYPE_3__ RSA ;
typedef  TYPE_4__ EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_bn_print (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 scalar_t__ pkey_is_pss (TYPE_4__ const*) ; 
 int /*<<< orphan*/  rsa_pss_param_print (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int sk_RSA_PRIME_INFO_num (int /*<<< orphan*/ ) ; 
 TYPE_2__* sk_RSA_PRIME_INFO_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pkey_rsa_print(BIO *bp, const EVP_PKEY *pkey, int off, int priv)
{
    const RSA *x = pkey->pkey.rsa;
    char *str;
    const char *s;
    int ret = 0, mod_len = 0, ex_primes;

    if (x->n != NULL)
        mod_len = BN_num_bits(x->n);
    ex_primes = sk_RSA_PRIME_INFO_num(x->prime_infos);

    if (!BIO_indent(bp, off, 128))
        goto err;

    if (BIO_printf(bp, "%s ", pkey_is_pss(pkey) ?  "RSA-PSS" : "RSA") <= 0)
        goto err;

    if (priv && x->d) {
        if (BIO_printf(bp, "Private-Key: (%d bit, %d primes)\n",
                       mod_len, ex_primes <= 0 ? 2 : ex_primes + 2) <= 0)
            goto err;
        str = "modulus:";
        s = "publicExponent:";
    } else {
        if (BIO_printf(bp, "Public-Key: (%d bit)\n", mod_len) <= 0)
            goto err;
        str = "Modulus:";
        s = "Exponent:";
    }
    if (!ASN1_bn_print(bp, str, x->n, NULL, off))
        goto err;
    if (!ASN1_bn_print(bp, s, x->e, NULL, off))
        goto err;
    if (priv) {
        int i;

        if (!ASN1_bn_print(bp, "privateExponent:", x->d, NULL, off))
            goto err;
        if (!ASN1_bn_print(bp, "prime1:", x->p, NULL, off))
            goto err;
        if (!ASN1_bn_print(bp, "prime2:", x->q, NULL, off))
            goto err;
        if (!ASN1_bn_print(bp, "exponent1:", x->dmp1, NULL, off))
            goto err;
        if (!ASN1_bn_print(bp, "exponent2:", x->dmq1, NULL, off))
            goto err;
        if (!ASN1_bn_print(bp, "coefficient:", x->iqmp, NULL, off))
            goto err;
        for (i = 0; i < sk_RSA_PRIME_INFO_num(x->prime_infos); i++) {
            /* print multi-prime info */
            BIGNUM *bn = NULL;
            RSA_PRIME_INFO *pinfo;
            int j;

            pinfo = sk_RSA_PRIME_INFO_value(x->prime_infos, i);
            for (j = 0; j < 3; j++) {
                if (!BIO_indent(bp, off, 128))
                    goto err;
                switch (j) {
                case 0:
                    if (BIO_printf(bp, "prime%d:", i + 3) <= 0)
                        goto err;
                    bn = pinfo->r;
                    break;
                case 1:
                    if (BIO_printf(bp, "exponent%d:", i + 3) <= 0)
                        goto err;
                    bn = pinfo->d;
                    break;
                case 2:
                    if (BIO_printf(bp, "coefficient%d:", i + 3) <= 0)
                        goto err;
                    bn = pinfo->t;
                    break;
                default:
                    break;
                }
                if (!ASN1_bn_print(bp, "", bn, NULL, off))
                    goto err;
            }
        }
    }
    if (pkey_is_pss(pkey) && !rsa_pss_param_print(bp, 1, x->pss, off))
        goto err;
    ret = 1;
 err:
    return ret;
}
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
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_D2I_AUTOPRIVATEKEY ; 
 int /*<<< orphan*/  ASN1_R_UNSUPPORTED_PUBLIC_KEY_TYPE ; 
 int /*<<< orphan*/  ASN1_TYPE ; 
 int /*<<< orphan*/  ASN1_TYPE_free ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_PKCS82PKEY (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_DSA ; 
 int EVP_PKEY_EC ; 
 int EVP_PKEY_RSA ; 
 int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO_free (int /*<<< orphan*/ *) ; 
 int STACK_OF (int /*<<< orphan*/ ) ; 
 int d2i_ASN1_SEQUENCE_ANY (int /*<<< orphan*/ *,unsigned char const**,long) ; 
 int /*<<< orphan*/ * d2i_PKCS8_PRIV_KEY_INFO (int /*<<< orphan*/ *,unsigned char const**,long) ; 
 int /*<<< orphan*/ * d2i_PrivateKey (int,int /*<<< orphan*/ **,unsigned char const**,long) ; 
 int inkey ; 
 int sk_ASN1_TYPE_num (int) ; 
 int /*<<< orphan*/  sk_ASN1_TYPE_pop_free (int,int /*<<< orphan*/ ) ; 

EVP_PKEY *d2i_AutoPrivateKey(EVP_PKEY **a, const unsigned char **pp,
                             long length)
{
    STACK_OF(ASN1_TYPE) *inkey;
    const unsigned char *p;
    int keytype;
    p = *pp;
    /*
     * Dirty trick: read in the ASN1 data into a STACK_OF(ASN1_TYPE): by
     * analyzing it we can determine the passed structure: this assumes the
     * input is surrounded by an ASN1 SEQUENCE.
     */
    inkey = d2i_ASN1_SEQUENCE_ANY(NULL, &p, length);
    p = *pp;
    /*
     * Since we only need to discern "traditional format" RSA and DSA keys we
     * can just count the elements.
     */
    if (sk_ASN1_TYPE_num(inkey) == 6)
        keytype = EVP_PKEY_DSA;
    else if (sk_ASN1_TYPE_num(inkey) == 4)
        keytype = EVP_PKEY_EC;
    else if (sk_ASN1_TYPE_num(inkey) == 3) { /* This seems to be PKCS8, not
                                              * traditional format */
        PKCS8_PRIV_KEY_INFO *p8 = d2i_PKCS8_PRIV_KEY_INFO(NULL, &p, length);
        EVP_PKEY *ret;

        sk_ASN1_TYPE_pop_free(inkey, ASN1_TYPE_free);
        if (!p8) {
            ASN1err(ASN1_F_D2I_AUTOPRIVATEKEY,
                    ASN1_R_UNSUPPORTED_PUBLIC_KEY_TYPE);
            return NULL;
        }
        ret = EVP_PKCS82PKEY(p8);
        PKCS8_PRIV_KEY_INFO_free(p8);
        if (ret == NULL)
            return NULL;
        *pp = p;
        if (a) {
            *a = ret;
        }
        return ret;
    } else
        keytype = EVP_PKEY_RSA;
    sk_ASN1_TYPE_pop_free(inkey, ASN1_TYPE_free);
    return d2i_PrivateKey(keytype, a, pp, length);
}
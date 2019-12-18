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
typedef  int /*<<< orphan*/  X509_SIG ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  int /*<<< orphan*/  PKCS12_SAFEBAG ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_get_cipherbynid (int) ; 
 int /*<<< orphan*/ * PKCS12_SAFEBAG_create0_pkcs8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PKCS8_encrypt (int,int /*<<< orphan*/  const*,char const*,int,unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_SIG_free (int /*<<< orphan*/ *) ; 

PKCS12_SAFEBAG *PKCS12_SAFEBAG_create_pkcs8_encrypt(int pbe_nid,
                                                    const char *pass,
                                                    int passlen,
                                                    unsigned char *salt,
                                                    int saltlen, int iter,
                                                    PKCS8_PRIV_KEY_INFO *p8inf)
{
    PKCS12_SAFEBAG *bag;
    const EVP_CIPHER *pbe_ciph;
    X509_SIG *p8;

    pbe_ciph = EVP_get_cipherbynid(pbe_nid);
    if (pbe_ciph)
        pbe_nid = -1;

    p8 = PKCS8_encrypt(pbe_nid, pbe_ciph, pass, passlen, salt, saltlen, iter,
                       p8inf);
    if (p8 == NULL)
        return NULL;

    bag = PKCS12_SAFEBAG_create0_pkcs8(p8);
    if (bag == NULL)
        X509_SIG_free(p8);

    return bag;
}
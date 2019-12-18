#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_15__ {unsigned char* data; int length; } ;
struct TYPE_14__ {int /*<<< orphan*/ * priv_key; } ;
struct TYPE_13__ {TYPE_1__* ameth; } ;
struct TYPE_12__ {int /*<<< orphan*/  pkey_id; } ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  TYPE_3__ DH ;
typedef  TYPE_4__ ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_to_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_STRING_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_secure_new () ; 
 int /*<<< orphan*/  DH_F_DH_PRIV_DECODE ; 
 int /*<<< orphan*/  DH_R_BN_ERROR ; 
 int /*<<< orphan*/  DH_free (TYPE_3__*) ; 
 int /*<<< orphan*/  DH_generate_key (TYPE_3__*) ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_assign (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  EVP_R_DECODE_ERROR ; 
 int /*<<< orphan*/  PKCS8_pkey_get0 (int /*<<< orphan*/ *,unsigned char const**,int*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int V_ASN1_SEQUENCE ; 
 int /*<<< orphan*/  X509_ALGOR_get0 (int /*<<< orphan*/ *,int*,void const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * d2i_ASN1_INTEGER (int /*<<< orphan*/ *,unsigned char const**,int) ; 
 TYPE_3__* d2i_dhp (TYPE_2__*,unsigned char const**,int) ; 

__attribute__((used)) static int dh_priv_decode(EVP_PKEY *pkey, const PKCS8_PRIV_KEY_INFO *p8)
{
    const unsigned char *p, *pm;
    int pklen, pmlen;
    int ptype;
    const void *pval;
    const ASN1_STRING *pstr;
    const X509_ALGOR *palg;
    ASN1_INTEGER *privkey = NULL;

    DH *dh = NULL;

    if (!PKCS8_pkey_get0(NULL, &p, &pklen, &palg, p8))
        return 0;

    X509_ALGOR_get0(NULL, &ptype, &pval, palg);

    if (ptype != V_ASN1_SEQUENCE)
        goto decerr;
    if ((privkey = d2i_ASN1_INTEGER(NULL, &p, pklen)) == NULL)
        goto decerr;

    pstr = pval;
    pm = pstr->data;
    pmlen = pstr->length;
    if ((dh = d2i_dhp(pkey, &pm, pmlen)) == NULL)
        goto decerr;

    /* We have parameters now set private key */
    if ((dh->priv_key = BN_secure_new()) == NULL
        || !ASN1_INTEGER_to_BN(privkey, dh->priv_key)) {
        DHerr(DH_F_DH_PRIV_DECODE, DH_R_BN_ERROR);
        goto dherr;
    }
    /* Calculate public key */
    if (!DH_generate_key(dh))
        goto dherr;

    EVP_PKEY_assign(pkey, pkey->ameth->pkey_id, dh);

    ASN1_STRING_clear_free(privkey);

    return 1;

 decerr:
    DHerr(DH_F_DH_PRIV_DECODE, EVP_R_DECODE_ERROR);
 dherr:
    DH_free(dh);
    ASN1_STRING_clear_free(privkey);
    return 0;
}
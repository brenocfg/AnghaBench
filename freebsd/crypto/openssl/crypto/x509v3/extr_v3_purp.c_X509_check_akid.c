#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_11__ {scalar_t__ skid; } ;
typedef  TYPE_2__ X509 ;
struct TYPE_13__ {int /*<<< orphan*/ * issuer; scalar_t__ serial; scalar_t__ keyid; } ;
struct TYPE_10__ {int /*<<< orphan*/ * dirn; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_1__ d; } ;
typedef  int /*<<< orphan*/  GENERAL_NAMES ;
typedef  TYPE_3__ GENERAL_NAME ;
typedef  TYPE_4__ AUTHORITY_KEYID ;

/* Variables and functions */
 scalar_t__ ASN1_INTEGER_cmp (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ASN1_OCTET_STRING_cmp (scalar_t__,scalar_t__) ; 
 scalar_t__ GEN_DIRNAME ; 
 scalar_t__ X509_NAME_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH ; 
 int X509_V_ERR_AKID_SKID_MISMATCH ; 
 int X509_V_OK ; 
 int /*<<< orphan*/  X509_get_issuer_name (TYPE_2__*) ; 
 int /*<<< orphan*/  X509_get_serialNumber (TYPE_2__*) ; 
 int sk_GENERAL_NAME_num (int /*<<< orphan*/ *) ; 
 TYPE_3__* sk_GENERAL_NAME_value (int /*<<< orphan*/ *,int) ; 

int X509_check_akid(X509 *issuer, AUTHORITY_KEYID *akid)
{

    if (!akid)
        return X509_V_OK;

    /* Check key ids (if present) */
    if (akid->keyid && issuer->skid &&
        ASN1_OCTET_STRING_cmp(akid->keyid, issuer->skid))
        return X509_V_ERR_AKID_SKID_MISMATCH;
    /* Check serial number */
    if (akid->serial &&
        ASN1_INTEGER_cmp(X509_get_serialNumber(issuer), akid->serial))
        return X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH;
    /* Check issuer name */
    if (akid->issuer) {
        /*
         * Ugh, for some peculiar reason AKID includes SEQUENCE OF
         * GeneralName. So look for a DirName. There may be more than one but
         * we only take any notice of the first.
         */
        GENERAL_NAMES *gens;
        GENERAL_NAME *gen;
        X509_NAME *nm = NULL;
        int i;
        gens = akid->issuer;
        for (i = 0; i < sk_GENERAL_NAME_num(gens); i++) {
            gen = sk_GENERAL_NAME_value(gens, i);
            if (gen->type == GEN_DIRNAME) {
                nm = gen->d.dirn;
                break;
            }
        }
        if (nm && X509_NAME_cmp(nm, X509_get_issuer_name(issuer)))
            return X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH;
    }
    return X509_V_OK;
}
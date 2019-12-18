#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
struct TYPE_7__ {int (* sig_print ) (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ EVP_PKEY_ASN1_METHOD ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 scalar_t__ BIO_puts (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* EVP_PKEY_asn1_find (int /*<<< orphan*/ *,int) ; 
 int NID_undef ; 
 scalar_t__ OBJ_find_sigid_algs (int,int*,int*) ; 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int X509_signature_dump (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ i2a_ASN1_OBJECT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

int X509_signature_print(BIO *bp, const X509_ALGOR *sigalg,
                         const ASN1_STRING *sig)
{
    int sig_nid;
    if (BIO_puts(bp, "    Signature Algorithm: ") <= 0)
        return 0;
    if (i2a_ASN1_OBJECT(bp, sigalg->algorithm) <= 0)
        return 0;

    sig_nid = OBJ_obj2nid(sigalg->algorithm);
    if (sig_nid != NID_undef) {
        int pkey_nid, dig_nid;
        const EVP_PKEY_ASN1_METHOD *ameth;
        if (OBJ_find_sigid_algs(sig_nid, &dig_nid, &pkey_nid)) {
            ameth = EVP_PKEY_asn1_find(NULL, pkey_nid);
            if (ameth && ameth->sig_print)
                return ameth->sig_print(bp, sigalg, sig, 9, 0);
        }
    }
    if (sig)
        return X509_signature_dump(bp, sig, 9);
    else if (BIO_puts(bp, "\n") <= 0)
        return 0;
    return 1;
}
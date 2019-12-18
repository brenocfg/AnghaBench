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
struct TYPE_3__ {int /*<<< orphan*/ * pkey; } ;
typedef  TYPE_1__ X509_PUBKEY ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int ASN1_OP_D2I_POST ; 
 int ASN1_OP_FREE_POST ; 
 int /*<<< orphan*/  ERR_pop_to_mark () ; 
 int /*<<< orphan*/  ERR_set_mark () ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int x509_pubkey_decode (int /*<<< orphan*/ **,TYPE_1__*) ; 

__attribute__((used)) static int pubkey_cb(int operation, ASN1_VALUE **pval, const ASN1_ITEM *it,
                     void *exarg)
{
    if (operation == ASN1_OP_FREE_POST) {
        X509_PUBKEY *pubkey = (X509_PUBKEY *)*pval;
        EVP_PKEY_free(pubkey->pkey);
    } else if (operation == ASN1_OP_D2I_POST) {
        /* Attempt to decode public key and cache in pubkey structure. */
        X509_PUBKEY *pubkey = (X509_PUBKEY *)*pval;
        EVP_PKEY_free(pubkey->pkey);
        pubkey->pkey = NULL;
        /*
         * Opportunistically decode the key but remove any non fatal errors
         * from the queue. Subsequent explicit attempts to decode/use the key
         * will return an appropriate error.
         */
        ERR_set_mark();
        if (x509_pubkey_decode(&pubkey->pkey, pubkey) == -1)
            return 0;
        ERR_pop_to_mark();
    }
    return 1;
}
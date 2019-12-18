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
struct TYPE_2__ {int /*<<< orphan*/  cert; } ;
typedef  TYPE_1__ PKCS7_RECIP_INFO ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int ASN1_OP_FREE_POST ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ri_cb(int operation, ASN1_VALUE **pval, const ASN1_ITEM *it,
                 void *exarg)
{
    if (operation == ASN1_OP_FREE_POST) {
        PKCS7_RECIP_INFO *ri = (PKCS7_RECIP_INFO *)*pval;
        X509_free(ri->cert);
    }
    return 1;
}
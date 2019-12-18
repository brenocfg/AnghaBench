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
struct TYPE_2__ {int /*<<< orphan*/ * dpname; } ;
typedef  TYPE_1__ DIST_POINT_NAME ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
#define  ASN1_OP_FREE_POST 129 
#define  ASN1_OP_NEW_POST 128 
 int /*<<< orphan*/  X509_NAME_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dpn_cb(int operation, ASN1_VALUE **pval, const ASN1_ITEM *it,
                  void *exarg)
{
    DIST_POINT_NAME *dpn = (DIST_POINT_NAME *)*pval;

    switch (operation) {
    case ASN1_OP_NEW_POST:
        dpn->dpname = NULL;
        break;

    case ASN1_OP_FREE_POST:
        X509_NAME_free(dpn->dpname);
        break;
    }
    return 1;
}
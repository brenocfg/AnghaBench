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
struct TYPE_11__ {int /*<<< orphan*/ * fullname; } ;
struct TYPE_13__ {int type; TYPE_2__ name; int /*<<< orphan*/ * dpname; } ;
struct TYPE_10__ {int /*<<< orphan*/ * directoryName; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_1__ d; } ;
typedef  int /*<<< orphan*/  GENERAL_NAMES ;
typedef  TYPE_3__ GENERAL_NAME ;
typedef  TYPE_4__ DIST_POINT_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  GENERAL_NAME_cmp (TYPE_3__*,TYPE_3__*) ; 
 scalar_t__ GEN_DIRNAME ; 
 int /*<<< orphan*/  X509_NAME_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sk_GENERAL_NAME_num (int /*<<< orphan*/ *) ; 
 TYPE_3__* sk_GENERAL_NAME_value (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int idp_check_dp(DIST_POINT_NAME *a, DIST_POINT_NAME *b)
{
    X509_NAME *nm = NULL;
    GENERAL_NAMES *gens = NULL;
    GENERAL_NAME *gena, *genb;
    int i, j;
    if (!a || !b)
        return 1;
    if (a->type == 1) {
        if (!a->dpname)
            return 0;
        /* Case 1: two X509_NAME */
        if (b->type == 1) {
            if (!b->dpname)
                return 0;
            if (!X509_NAME_cmp(a->dpname, b->dpname))
                return 1;
            else
                return 0;
        }
        /* Case 2: set name and GENERAL_NAMES appropriately */
        nm = a->dpname;
        gens = b->name.fullname;
    } else if (b->type == 1) {
        if (!b->dpname)
            return 0;
        /* Case 2: set name and GENERAL_NAMES appropriately */
        gens = a->name.fullname;
        nm = b->dpname;
    }

    /* Handle case 2 with one GENERAL_NAMES and one X509_NAME */
    if (nm) {
        for (i = 0; i < sk_GENERAL_NAME_num(gens); i++) {
            gena = sk_GENERAL_NAME_value(gens, i);
            if (gena->type != GEN_DIRNAME)
                continue;
            if (!X509_NAME_cmp(nm, gena->d.directoryName))
                return 1;
        }
        return 0;
    }

    /* Else case 3: two GENERAL_NAMES */

    for (i = 0; i < sk_GENERAL_NAME_num(a->name.fullname); i++) {
        gena = sk_GENERAL_NAME_value(a->name.fullname, i);
        for (j = 0; j < sk_GENERAL_NAME_num(b->name.fullname); j++) {
            genb = sk_GENERAL_NAME_value(b->name.fullname, j);
            if (!GENERAL_NAME_cmp(gena, genb))
                return 1;
        }
    }

    return 0;

}
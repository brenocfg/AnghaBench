#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ (* adb_cb ) (long*) ;int tblcount; TYPE_1__ const* default_tt; TYPE_2__* tbl; TYPE_1__ const* null_tt; int /*<<< orphan*/  offset; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  item; } ;
struct TYPE_8__ {long value; TYPE_1__ const tt; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_1__ ASN1_TEMPLATE ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;
typedef  TYPE_2__ ASN1_ADB_TABLE ;
typedef  TYPE_3__ ASN1_ADB ;

/* Variables and functions */
 TYPE_3__* ASN1_ADB_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_F_ASN1_DO_ADB ; 
 long ASN1_INTEGER_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_R_UNSUPPORTED_ANY_DEFINED_BY_TYPE ; 
 int ASN1_TFLG_ADB_MASK ; 
 int ASN1_TFLG_ADB_OID ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long OBJ_obj2nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** offset2ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (long*) ; 

const ASN1_TEMPLATE *asn1_do_adb(ASN1_VALUE **pval, const ASN1_TEMPLATE *tt,
                                 int nullerr)
{
    const ASN1_ADB *adb;
    const ASN1_ADB_TABLE *atbl;
    long selector;
    ASN1_VALUE **sfld;
    int i;
    if (!(tt->flags & ASN1_TFLG_ADB_MASK))
        return tt;

    /* Else ANY DEFINED BY ... get the table */
    adb = ASN1_ADB_ptr(tt->item);

    /* Get the selector field */
    sfld = offset2ptr(*pval, adb->offset);

    /* Check if NULL */
    if (*sfld == NULL) {
        if (!adb->null_tt)
            goto err;
        return adb->null_tt;
    }

    /*
     * Convert type to a long: NB: don't check for NID_undef here because it
     * might be a legitimate value in the table
     */
    if (tt->flags & ASN1_TFLG_ADB_OID)
        selector = OBJ_obj2nid((ASN1_OBJECT *)*sfld);
    else
        selector = ASN1_INTEGER_get((ASN1_INTEGER *)*sfld);

    /* Let application callback translate value */
    if (adb->adb_cb != NULL && adb->adb_cb(&selector) == 0) {
        ASN1err(ASN1_F_ASN1_DO_ADB, ASN1_R_UNSUPPORTED_ANY_DEFINED_BY_TYPE);
        return NULL;
    }

    /*
     * Try to find matching entry in table Maybe should check application
     * types first to allow application override? Might also be useful to
     * have a flag which indicates table is sorted and we can do a binary
     * search. For now stick to a linear search.
     */

    for (atbl = adb->tbl, i = 0; i < adb->tblcount; i++, atbl++)
        if (atbl->value == selector)
            return &atbl->tt;

    /* FIXME: need to search application table too */

    /* No match, return default type */
    if (!adb->default_tt)
        goto err;
    return adb->default_tt;

 err:
    /* FIXME: should log the value or OID of unsupported type */
    if (nullerr)
        ASN1err(ASN1_F_ASN1_DO_ADB, ASN1_R_UNSUPPORTED_ANY_DEFINED_BY_TYPE);
    return NULL;
}
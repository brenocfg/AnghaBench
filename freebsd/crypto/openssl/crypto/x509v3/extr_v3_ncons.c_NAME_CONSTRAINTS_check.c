#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME_ENTRY ;
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_13__ {int /*<<< orphan*/  altname; } ;
typedef  TYPE_2__ X509 ;
struct TYPE_16__ {scalar_t__ type; } ;
struct TYPE_12__ {TYPE_9__* rfc822Name; int /*<<< orphan*/ * directoryName; } ;
struct TYPE_15__ {TYPE_1__ d; int /*<<< orphan*/  type; } ;
struct TYPE_14__ {int /*<<< orphan*/  excludedSubtrees; int /*<<< orphan*/  permittedSubtrees; } ;
typedef  TYPE_3__ NAME_CONSTRAINTS ;
typedef  TYPE_4__ GENERAL_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_DIRNAME ; 
 int /*<<< orphan*/  GEN_EMAIL ; 
 int NAME_CHECK_MAX ; 
 int /*<<< orphan*/  NID_pkcs9_emailAddress ; 
 scalar_t__ V_ASN1_IA5STRING ; 
 TYPE_9__* X509_NAME_ENTRY_get_data (int /*<<< orphan*/  const*) ; 
 scalar_t__ X509_NAME_entry_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_NAME_get_entry (int /*<<< orphan*/ *,int) ; 
 int X509_NAME_get_index_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int X509_V_ERR_UNSPECIFIED ; 
 int X509_V_ERR_UNSUPPORTED_NAME_SYNTAX ; 
 int X509_V_OK ; 
 int /*<<< orphan*/ * X509_get_subject_name (TYPE_2__*) ; 
 int /*<<< orphan*/  add_lengths (int*,int,int) ; 
 int nc_match (TYPE_4__*,TYPE_3__*) ; 
 int sk_GENERAL_NAME_num (int /*<<< orphan*/ ) ; 
 TYPE_4__* sk_GENERAL_NAME_value (int /*<<< orphan*/ ,int) ; 
 int sk_GENERAL_SUBTREE_num (int /*<<< orphan*/ ) ; 

int NAME_CONSTRAINTS_check(X509 *x, NAME_CONSTRAINTS *nc)
{
    int r, i, name_count, constraint_count;
    X509_NAME *nm;

    nm = X509_get_subject_name(x);

    /*
     * Guard against certificates with an excessive number of names or
     * constraints causing a computationally expensive name constraints check.
     */
    if (!add_lengths(&name_count, X509_NAME_entry_count(nm),
                     sk_GENERAL_NAME_num(x->altname))
        || !add_lengths(&constraint_count,
                        sk_GENERAL_SUBTREE_num(nc->permittedSubtrees),
                        sk_GENERAL_SUBTREE_num(nc->excludedSubtrees))
        || (name_count > 0 && constraint_count > NAME_CHECK_MAX / name_count))
        return X509_V_ERR_UNSPECIFIED;

    if (X509_NAME_entry_count(nm) > 0) {
        GENERAL_NAME gntmp;
        gntmp.type = GEN_DIRNAME;
        gntmp.d.directoryName = nm;

        r = nc_match(&gntmp, nc);

        if (r != X509_V_OK)
            return r;

        gntmp.type = GEN_EMAIL;

        /* Process any email address attributes in subject name */

        for (i = -1;;) {
            const X509_NAME_ENTRY *ne;

            i = X509_NAME_get_index_by_NID(nm, NID_pkcs9_emailAddress, i);
            if (i == -1)
                break;
            ne = X509_NAME_get_entry(nm, i);
            gntmp.d.rfc822Name = X509_NAME_ENTRY_get_data(ne);
            if (gntmp.d.rfc822Name->type != V_ASN1_IA5STRING)
                return X509_V_ERR_UNSUPPORTED_NAME_SYNTAX;

            r = nc_match(&gntmp, nc);

            if (r != X509_V_OK)
                return r;
        }

    }

    for (i = 0; i < sk_GENERAL_NAME_num(x->altname); i++) {
        GENERAL_NAME *gen = sk_GENERAL_NAME_value(x->altname, i);
        r = nc_match(gen, nc);
        if (r != X509_V_OK)
            return r;
    }

    return X509_V_OK;

}
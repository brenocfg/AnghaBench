#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_9__ {TYPE_2__* extensions; } ;
typedef  TYPE_4__ hdb_entry ;
struct TYPE_6__ {scalar_t__ element; } ;
struct TYPE_8__ {scalar_t__ mandatory; TYPE_1__ data; } ;
struct TYPE_7__ {size_t len; TYPE_3__* val; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDB_ERR_MANDATORY_OPTION ; 
 scalar_t__ choice_HDB_extension_data_asn1_ellipsis ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

krb5_error_code
hdb_entry_check_mandatory(krb5_context context, const hdb_entry *ent)
{
    size_t i;

    if (ent->extensions == NULL)
	return 0;

    /*
     * check for unknown extensions and if they where tagged mandatory
     */

    for (i = 0; i < ent->extensions->len; i++) {
	if (ent->extensions->val[i].data.element !=
	    choice_HDB_extension_data_asn1_ellipsis)
	    continue;
	if (ent->extensions->val[i].mandatory) {
	    krb5_set_error_message(context, HDB_ERR_MANDATORY_OPTION,
				   "Principal have unknown "
				   "mandatory extension");
	    return HDB_ERR_MANDATORY_OPTION;
	}
    }
    return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  hdb_entry ;
struct TYPE_5__ {scalar_t__ last_pw_change; } ;
struct TYPE_6__ {TYPE_1__ u; int /*<<< orphan*/  element; } ;
struct TYPE_7__ {TYPE_2__ data; int /*<<< orphan*/  mandatory; } ;
typedef  TYPE_3__ HDB_extension ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  choice_HDB_extension_data_last_pw_change ; 
 int /*<<< orphan*/  hdb_replace_extension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

krb5_error_code
hdb_entry_set_pw_change_time(krb5_context context,
			     hdb_entry *entry,
			     time_t t)
{
    HDB_extension ext;

    ext.mandatory = FALSE;
    ext.data.element = choice_HDB_extension_data_last_pw_change;
    if (t == 0)
	t = time(NULL);
    ext.data.u.last_pw_change = t;

    return hdb_replace_extension(context, entry, &ext);
}
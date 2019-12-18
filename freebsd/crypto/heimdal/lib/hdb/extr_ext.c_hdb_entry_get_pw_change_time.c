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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  hdb_entry ;
struct TYPE_5__ {int /*<<< orphan*/  last_pw_change; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
struct TYPE_7__ {TYPE_2__ data; } ;
typedef  TYPE_3__ HDB_extension ;

/* Variables and functions */
 int /*<<< orphan*/  choice_HDB_extension_data_last_pw_change ; 
 TYPE_3__* hdb_find_extension (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

krb5_error_code
hdb_entry_get_pw_change_time(const hdb_entry *entry, time_t *t)
{
    const HDB_extension *ext;

    ext = hdb_find_extension(entry, choice_HDB_extension_data_last_pw_change);
    if (ext)
	*t = ext->data.u.last_pw_change;
    else
	*t = 0;

    return 0;
}
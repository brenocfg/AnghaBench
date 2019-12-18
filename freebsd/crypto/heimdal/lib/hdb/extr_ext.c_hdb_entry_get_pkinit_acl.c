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
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  hdb_entry ;
struct TYPE_5__ {int /*<<< orphan*/  pkinit_acl; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
struct TYPE_7__ {TYPE_2__ data; } ;
typedef  TYPE_3__ HDB_extension ;
typedef  int /*<<< orphan*/  HDB_Ext_PKINIT_acl ;

/* Variables and functions */
 int /*<<< orphan*/  choice_HDB_extension_data_pkinit_acl ; 
 TYPE_3__* hdb_find_extension (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

krb5_error_code
hdb_entry_get_pkinit_acl(const hdb_entry *entry, const HDB_Ext_PKINIT_acl **a)
{
    const HDB_extension *ext;

    ext = hdb_find_extension(entry, choice_HDB_extension_data_pkinit_acl);
    if (ext)
	*a = &ext->data.u.pkinit_acl;
    else
	*a = NULL;

    return 0;
}
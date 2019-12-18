#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hdb_master_key ;
struct TYPE_4__ {int vno; } ;
struct TYPE_5__ {TYPE_1__ keytab; } ;

/* Variables and functions */

int
_hdb_mkey_version(hdb_master_key mkey)
{
    return mkey->keytab.vno;
}
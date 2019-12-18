#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hdb_dbinfo {int /*<<< orphan*/  const* binding; } ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_config_binding ;

/* Variables and functions */

const krb5_config_binding *
hdb_dbinfo_get_binding(krb5_context context, struct hdb_dbinfo *dbp)
{
    return dbp->binding;
}
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
struct hdb_dbinfo {char const* log_file; } ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */

const char *
hdb_dbinfo_get_log_file(krb5_context context, struct hdb_dbinfo *dbp)
{
    return dbp->log_file;
}
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
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  hdb_entry ;

/* Variables and functions */
 int /*<<< orphan*/  choice_HDB_extension_data_password ; 
 int hdb_clear_extension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
hdb_entry_clear_password(krb5_context context, hdb_entry *entry)
{
    return hdb_clear_extension(context, entry,
			       choice_HDB_extension_data_password);
}
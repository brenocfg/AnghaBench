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
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  hdb_entry ;
typedef  int /*<<< orphan*/  Key ;

/* Variables and functions */
 int /*<<< orphan*/  hdb_next_enctype2key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

krb5_error_code
hdb_enctype2key(krb5_context context,
		hdb_entry *e,
		krb5_enctype enctype,
		Key **key)
{
    *key = NULL;
    return hdb_next_enctype2key(context, e, enctype, key);
}
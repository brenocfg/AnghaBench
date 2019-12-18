#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_3__ {char* data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  hdb_entry ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ entry2string_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/ * krb5_storage_emem () ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_to_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_storage_write (int /*<<< orphan*/ *,char*,int) ; 

krb5_error_code
hdb_entry2string (krb5_context context, hdb_entry *ent, char **str)
{
    krb5_error_code ret;
    krb5_data data;
    krb5_storage *sp;

    sp = krb5_storage_emem();
    if(sp == NULL) {
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }

    ret = entry2string_int(context, sp, ent);
    if(ret) {
	krb5_storage_free(sp);
	return ret;
    }

    krb5_storage_write(sp, "\0", 1);
    krb5_storage_to_data(sp, &data);
    krb5_storage_free(sp);
    *str = data.data;
    return 0;
}
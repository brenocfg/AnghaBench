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
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_3__ {int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ hdb_entry_ex ;
typedef  int /*<<< orphan*/  HDB ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ entry2string_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_storage_write (int /*<<< orphan*/ *,char*,int) ; 

krb5_error_code
hdb_print_entry(krb5_context context, HDB *db, hdb_entry_ex *entry, void *data)
{
    krb5_error_code ret;
    krb5_storage *sp;

    FILE *f = data;

    fflush(f);
    sp = krb5_storage_from_fd(fileno(f));
    if(sp == NULL) {
	krb5_set_error_message(context, ENOMEM, "malloc: out of memory");
	return ENOMEM;
    }

    ret = entry2string_int(context, sp, &entry->entry);
    if(ret) {
	krb5_storage_free(sp);
	return ret;
    }

    krb5_storage_write(sp, "\n", 1);
    krb5_storage_free(sp);
    return 0;
}
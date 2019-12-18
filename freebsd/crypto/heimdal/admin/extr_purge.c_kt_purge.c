#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct purge_options {int /*<<< orphan*/  age_string; } ;
struct e {scalar_t__ max_vno; int timestamp; } ;
typedef  int /*<<< orphan*/  krb5_kt_cursor ;
struct TYPE_5__ {scalar_t__ vno; int /*<<< orphan*/  principal; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ krb5_keytab_entry ;
typedef  int /*<<< orphan*/ * krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  add_entry (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct e**) ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  delete_list (struct e*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct e* get_entry (int /*<<< orphan*/ ,struct e*) ; 
 int /*<<< orphan*/  keytab_string ; 
 int /*<<< orphan*/  krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_end_seq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_kt_free_entry (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ krb5_kt_next_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_remove_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ krb5_kt_start_seq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * ktutil_open_keytab () ; 
 int parse_time (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__) ; 
 int time (int /*<<< orphan*/ *) ; 
 scalar_t__ verbose_flag ; 

int
kt_purge(struct purge_options *opt, int argc, char **argv)
{
    krb5_error_code ret = 0;
    krb5_kt_cursor cursor;
    krb5_keytab keytab;
    krb5_keytab_entry entry;
    int age;
    struct e *head = NULL;
    time_t judgement_day;

    age = parse_time(opt->age_string, "s");
    if(age < 0) {
	krb5_warnx(context, "unparasable time `%s'", opt->age_string);
	return 1;
    }

    if((keytab = ktutil_open_keytab()) == NULL)
	return 1;

    ret = krb5_kt_start_seq_get(context, keytab, &cursor);
    if(ret){
	krb5_warn(context, ret, "%s", keytab_string);
	goto out;
    }

    while(krb5_kt_next_entry(context, keytab, &entry, &cursor) == 0) {
	add_entry (entry.principal, entry.vno, entry.timestamp, &head);
	krb5_kt_free_entry(context, &entry);
    }
    krb5_kt_end_seq_get(context, keytab, &cursor);

    judgement_day = time (NULL);

    ret = krb5_kt_start_seq_get(context, keytab, &cursor);
    if(ret){
	krb5_warn(context, ret, "%s", keytab_string);
	goto out;
    }

    while(krb5_kt_next_entry(context, keytab, &entry, &cursor) == 0) {
	struct e *e = get_entry (entry.principal, head);

	if (e == NULL) {
	    krb5_warnx (context, "ignoring extra entry");
	    continue;
	}

	if (entry.vno < e->max_vno
	    && judgement_day - e->timestamp > age) {
	    if (verbose_flag) {
		char *name_str;

		krb5_unparse_name (context, entry.principal, &name_str);
		printf ("removing %s vno %d\n", name_str, entry.vno);
		free (name_str);
	    }
	    ret = krb5_kt_remove_entry (context, keytab, &entry);
	    if (ret)
		krb5_warn (context, ret, "remove");
	}
	krb5_kt_free_entry(context, &entry);
    }
    ret = krb5_kt_end_seq_get(context, keytab, &cursor);

    delete_list (head);

 out:
    krb5_kt_close (context, keytab);
    return ret != 0;
}
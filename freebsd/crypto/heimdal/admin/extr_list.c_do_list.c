#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rk_strpool {int dummy; } ;
struct list_options {scalar_t__ keys_flag; scalar_t__ timestamp_flag; } ;
typedef  int /*<<< orphan*/  rtbl_t ;
typedef  int /*<<< orphan*/  krb5_kt_cursor ;
struct TYPE_7__ {int length; scalar_t__ data; } ;
struct TYPE_8__ {unsigned char keytype; TYPE_1__ keyvalue; } ;
struct TYPE_10__ {unsigned char vno; TYPE_3__* aliases; int /*<<< orphan*/  principal; TYPE_2__ keyblock; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_4__ krb5_keytab_entry ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {unsigned int len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RTBL_ALIGN_RIGHT ; 
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free (char*) ; 
 int krb5_enctype_to_string (int /*<<< orphan*/ ,unsigned char,char**) ; 
 int /*<<< orphan*/  krb5_format_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int krb5_kt_end_seq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_kt_free_entry (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ krb5_kt_next_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int krb5_kt_resolve (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int krb5_kt_start_seq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_unparse_name_fixed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* rk_strpoolcollect (struct rk_strpool*) ; 
 int /*<<< orphan*/  rk_strpoolprintf (struct rk_strpool*,char*,char*,char*) ; 
 int /*<<< orphan*/  rtbl_add_column_by_id (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_add_column_entry_by_id (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  rtbl_create () ; 
 int /*<<< orphan*/  rtbl_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtbl_set_separator (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned char) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 int strsep_copy (char const**,char*,char*,int) ; 

__attribute__((used)) static int
do_list(struct list_options *opt, const char *keytab_str)
{
    krb5_error_code ret;
    krb5_keytab keytab;
    krb5_keytab_entry entry;
    krb5_kt_cursor cursor;
    rtbl_t table;

    /* XXX specialcase the ANY type */
    if(strncasecmp(keytab_str, "ANY:", 4) == 0) {
	int flag = 0;
	char buf[1024];
	keytab_str += 4;
	ret = 0;
	while (strsep_copy((const char**)&keytab_str, ",",
			   buf, sizeof(buf)) != -1) {
	    if(flag)
		printf("\n");
	    if(do_list(opt, buf))
		ret = 1;
	    flag = 1;
	}
	return ret;
    }

    ret = krb5_kt_resolve(context, keytab_str, &keytab);
    if (ret) {
	krb5_warn(context, ret, "resolving keytab %s", keytab_str);
	return ret;
    }

    ret = krb5_kt_start_seq_get(context, keytab, &cursor);
    if(ret) {
	krb5_warn(context, ret, "krb5_kt_start_seq_get %s", keytab_str);
	krb5_kt_close(context, keytab);
	return ret;
    }

    printf ("%s:\n\n", keytab_str);

    table = rtbl_create();
    rtbl_add_column_by_id(table, 0, "Vno", RTBL_ALIGN_RIGHT);
    rtbl_add_column_by_id(table, 1, "Type", 0);
    rtbl_add_column_by_id(table, 2, "Principal", 0);
    if (opt->timestamp_flag)
	rtbl_add_column_by_id(table, 3, "Date", 0);
    if(opt->keys_flag)
	rtbl_add_column_by_id(table, 4, "Key", 0);
    rtbl_add_column_by_id(table, 5, "Aliases", 0);
    rtbl_set_separator(table, "  ");

    while(krb5_kt_next_entry(context, keytab, &entry, &cursor) == 0){
	char buf[1024], *s;

	snprintf(buf, sizeof(buf), "%d", entry.vno);
	rtbl_add_column_entry_by_id(table, 0, buf);

	ret = krb5_enctype_to_string(context,
				     entry.keyblock.keytype, &s);
	if (ret != 0) {
	    snprintf(buf, sizeof(buf), "unknown (%d)", entry.keyblock.keytype);
	    rtbl_add_column_entry_by_id(table, 1, buf);
	} else {
	    rtbl_add_column_entry_by_id(table, 1, s);
	    free(s);
	}

	krb5_unparse_name_fixed(context, entry.principal, buf, sizeof(buf));
	rtbl_add_column_entry_by_id(table, 2, buf);

	if (opt->timestamp_flag) {
	    krb5_format_time(context, entry.timestamp, buf,
			     sizeof(buf), FALSE);
	    rtbl_add_column_entry_by_id(table, 3, buf);
	}
	if(opt->keys_flag) {
	    size_t i;
	    s = malloc(2 * entry.keyblock.keyvalue.length + 1);
	    if (s == NULL) {
		krb5_warnx(context, "malloc failed");
		ret = ENOMEM;
		goto out;
	    }
	    for(i = 0; i < entry.keyblock.keyvalue.length; i++)
		snprintf(s + 2 * i, 3, "%02x",
			 ((unsigned char*)entry.keyblock.keyvalue.data)[i]);
	    rtbl_add_column_entry_by_id(table, 4, s);
	    free(s);
	}
	if (entry.aliases) {
	    unsigned int i;
	    struct rk_strpool *p = NULL;

	    for (i = 0; i< entry.aliases->len; i++) {
		krb5_unparse_name_fixed(context, entry.principal, buf, sizeof(buf));
		rk_strpoolprintf(p, "%s%s", buf,
				 i + 1 < entry.aliases->len ? ", " : "");

	    }
	    rtbl_add_column_entry_by_id(table, 5, rk_strpoolcollect(p));
	}

	krb5_kt_free_entry(context, &entry);
    }
    ret = krb5_kt_end_seq_get(context, keytab, &cursor);
    rtbl_format(table, stdout);

out:
    rtbl_destroy(table);

    krb5_kt_close(context, keytab);
    return ret;
}
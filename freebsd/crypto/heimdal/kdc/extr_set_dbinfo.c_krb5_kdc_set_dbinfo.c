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
struct krb5_kdc_configuration {int num_db; TYPE_1__** db; } ;
struct hdb_dbinfo {int dummy; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_3__ {int /*<<< orphan*/  (* hdb_destroy ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;

/* Variables and functions */
 scalar_t__ add_db (int /*<<< orphan*/ ,struct krb5_kdc_configuration*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 int /*<<< orphan*/  hdb_dbinfo_get_acl_file (int /*<<< orphan*/ ,struct hdb_dbinfo*) ; 
 int /*<<< orphan*/  hdb_dbinfo_get_dbname (int /*<<< orphan*/ ,struct hdb_dbinfo*) ; 
 int /*<<< orphan*/  hdb_dbinfo_get_label (int /*<<< orphan*/ ,struct hdb_dbinfo*) ; 
 int /*<<< orphan*/  hdb_dbinfo_get_mkey_file (int /*<<< orphan*/ ,struct hdb_dbinfo*) ; 
 struct hdb_dbinfo* hdb_dbinfo_get_next (struct hdb_dbinfo*,struct hdb_dbinfo*) ; 
 int /*<<< orphan*/  hdb_free_dbinfo (int /*<<< orphan*/ ,struct hdb_dbinfo**) ; 
 scalar_t__ hdb_get_dbinfo (int /*<<< orphan*/ ,struct hdb_dbinfo**) ; 
 int /*<<< orphan*/  kdc_log (int /*<<< orphan*/ ,struct krb5_kdc_configuration*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

krb5_error_code
krb5_kdc_set_dbinfo(krb5_context context, struct krb5_kdc_configuration *c)
{
    struct hdb_dbinfo *info, *d;
    krb5_error_code ret;
    int i;

    /* fetch the databases */
    ret = hdb_get_dbinfo(context, &info);
    if (ret)
	return ret;

    d = NULL;
    while ((d = hdb_dbinfo_get_next(info, d)) != NULL) {

	ret = add_db(context, c,
		     hdb_dbinfo_get_dbname(context, d),
		     hdb_dbinfo_get_mkey_file(context, d));
	if (ret)
	    goto out;

	kdc_log(context, c, 0, "label: %s",
		hdb_dbinfo_get_label(context, d));
	kdc_log(context, c, 0, "\tdbname: %s",
		hdb_dbinfo_get_dbname(context, d));
	kdc_log(context, c, 0, "\tmkey_file: %s",
		hdb_dbinfo_get_mkey_file(context, d));
	kdc_log(context, c, 0, "\tacl_file: %s",
		hdb_dbinfo_get_acl_file(context, d));
    }
    hdb_free_dbinfo(context, &info);

    return 0;
out:
    for (i = 0; i < c->num_db; i++)
	if (c->db[i] && c->db[i]->hdb_destroy)
	    (*c->db[i]->hdb_destroy)(context, c->db[i]);
    c->num_db = 0;
    free(c->db);
    c->db = NULL;

    hdb_free_dbinfo(context, &info);

    return ret;
}
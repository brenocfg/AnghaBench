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
struct krb5_plugin {int dummy; } ;
struct hdb_method {scalar_t__ interface_version; scalar_t__ (* create ) (int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const*) ;int /*<<< orphan*/  prefix; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  HDB ;

/* Variables and functions */
 char* HDB_DEFAULT_DB ; 
 scalar_t__ HDB_INTERFACE_VERSION ; 
 int /*<<< orphan*/  PLUGIN_TYPE_DATA ; 
 scalar_t__ _krb5_plugin_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct krb5_plugin**) ; 
 int /*<<< orphan*/  _krb5_plugin_free (struct krb5_plugin*) ; 
 struct krb5_plugin* _krb5_plugin_get_next (struct krb5_plugin*) ; 
 struct hdb_method* _krb5_plugin_get_symbol (struct krb5_plugin*) ; 
 struct hdb_method* find_dynamic_method (int /*<<< orphan*/ ,char const*,char const**) ; 
 struct hdb_method* find_method (char const*,char const**) ; 
 int /*<<< orphan*/  initialize_hdb_error_table_r ; 
 int /*<<< orphan*/  krb5_add_et_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const*) ; 

krb5_error_code
hdb_create(krb5_context context, HDB **db, const char *filename)
{
    const struct hdb_method *h;
    const char *residual;
    krb5_error_code ret;
    struct krb5_plugin *list = NULL, *e;

    if(filename == NULL)
	filename = HDB_DEFAULT_DB;
    krb5_add_et_list(context, initialize_hdb_error_table_r);
    h = find_method (filename, &residual);

    if (h == NULL) {
	    ret = _krb5_plugin_find(context, PLUGIN_TYPE_DATA, "hdb", &list);
	    if(ret == 0 && list != NULL) {
		    for (e = list; e != NULL; e = _krb5_plugin_get_next(e)) {
			    h = _krb5_plugin_get_symbol(e);
			    if (strncmp (filename, h->prefix, strlen(h->prefix)) == 0
				&& h->interface_version == HDB_INTERFACE_VERSION) {
				    residual = filename + strlen(h->prefix);
				    break;
			    }
		    }
		    if (e == NULL) {
			    h = NULL;
			    _krb5_plugin_free(list);
		    }
	    }
    }

#ifdef HAVE_DLOPEN
    if (h == NULL)
	h = find_dynamic_method (context, filename, &residual);
#endif
    if (h == NULL)
	krb5_errx(context, 1, "No database support for %s", filename);
    return (*h->create)(context, db, residual);
}
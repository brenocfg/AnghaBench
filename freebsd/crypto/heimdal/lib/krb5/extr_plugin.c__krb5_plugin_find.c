#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; void* symbol; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dsohandle; } ;
struct TYPE_6__ {TYPE_2__ symbol; TYPE_1__ dso; } ;
struct plugin {int type; TYPE_3__ u; struct plugin* next; } ;
struct krb5_plugin {int dummy; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  enum krb5_plugin_type { ____Placeholder_krb5_plugin_type } krb5_plugin_type ;

/* Variables and functions */
#define  DSO 129 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
#define  SYMBOL 128 
 int /*<<< orphan*/  _krb5_plugin_free (struct krb5_plugin*) ; 
 scalar_t__ add_symbol (int /*<<< orphan*/ ,struct krb5_plugin**,void*) ; 
 void* dlsym (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*,char const*) ; 
 int /*<<< orphan*/  load_plugins (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plugin_mutex ; 
 struct plugin* registered ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

krb5_error_code
_krb5_plugin_find(krb5_context context,
		  enum krb5_plugin_type type,
		  const char *name,
		  struct krb5_plugin **list)
{
    struct plugin *e;
    krb5_error_code ret;

    *list = NULL;

    HEIMDAL_MUTEX_lock(&plugin_mutex);

    load_plugins(context);

    for (ret = 0, e = registered; e != NULL; e = e->next) {
	switch(e->type) {
	case DSO: {
	    void *sym;
	    if (e->u.dso.dsohandle == NULL)
		continue;
	    sym = dlsym(e->u.dso.dsohandle, name);
	    if (sym)
		ret = add_symbol(context, list, sym);
	    break;
	}
	case SYMBOL:
	    if (strcmp(e->u.symbol.name, name) == 0 && e->u.symbol.type == type)
		ret = add_symbol(context, list, e->u.symbol.symbol);
	    break;
	}
	if (ret) {
	    _krb5_plugin_free(*list);
	    *list = NULL;
	}
    }

    HEIMDAL_MUTEX_unlock(&plugin_mutex);
    if (ret)
	return ret;

    if (*list == NULL) {
	krb5_set_error_message(context, ENOENT, "Did not find a plugin for %s", name);
	return ENOENT;
    }

    return 0;
}
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
struct krb5_plugin {int dummy; } ;
struct krb5_krbhst_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  realm; } ;
struct TYPE_3__ {scalar_t__ minor_version; scalar_t__ (* lookup ) (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct krb5_krbhst_data*) ;int /*<<< orphan*/  (* fini ) (void*) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ ,void**) ;} ;
typedef  TYPE_1__ krb5plugin_service_locate_ftable ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  enum locate_service_type { ____Placeholder_locate_service_type } locate_service_type ;

/* Variables and functions */
 int /*<<< orphan*/  KD_CONFIG_EXISTS ; 
 int /*<<< orphan*/  KRB5_PLUGIN_LOCATE ; 
 scalar_t__ KRB5_PLUGIN_NO_HANDLE ; 
 int /*<<< orphan*/  N_ (char*,char*) ; 
 int /*<<< orphan*/  PLUGIN_TYPE_DATA ; 
 int /*<<< orphan*/  _krb5_debug (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _krb5_plugin_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct krb5_plugin**) ; 
 int /*<<< orphan*/  _krb5_plugin_free (struct krb5_plugin*) ; 
 struct krb5_plugin* _krb5_plugin_get_next (struct krb5_plugin*) ; 
 TYPE_1__* _krb5_plugin_get_symbol (struct krb5_plugin*) ; 
 int /*<<< orphan*/  add_locate ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ stub2 (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct krb5_krbhst_data*) ; 
 int /*<<< orphan*/  stub3 (void*) ; 

__attribute__((used)) static void
plugin_get_hosts(krb5_context context,
		 struct krb5_krbhst_data *kd,
		 enum locate_service_type type)
{
    struct krb5_plugin *list = NULL, *e;
    krb5_error_code ret;

    ret = _krb5_plugin_find(context, PLUGIN_TYPE_DATA,
			    KRB5_PLUGIN_LOCATE, &list);
    if(ret != 0 || list == NULL)
	return;

    for (e = list; e != NULL; e = _krb5_plugin_get_next(e)) {
	krb5plugin_service_locate_ftable *service;
	void *ctx;

	service = _krb5_plugin_get_symbol(e);
	if (service->minor_version != 0)
	    continue;

	(*service->init)(context, &ctx);
	ret = (*service->lookup)(ctx, type, kd->realm, 0, 0, add_locate, kd);
	(*service->fini)(ctx);
	if (ret && ret != KRB5_PLUGIN_NO_HANDLE) {
	    krb5_set_error_message(context, ret,
				   N_("Locate plugin failed to lookup realm %s: %d", ""),
				   kd->realm, ret);
	    break;
	} else if (ret == 0) {
	    _krb5_debug(context, 2, "plugin found result for realm %s", kd->realm);
	    kd->flags |= KD_CONFIG_EXISTS;
	}

    }
    _krb5_plugin_free(list);
}
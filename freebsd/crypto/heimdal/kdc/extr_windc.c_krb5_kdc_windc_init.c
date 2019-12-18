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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_3__ {scalar_t__ minor_version; int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ KRB5_WINDC_PLUGIN_MINOR ; 
 int /*<<< orphan*/  PLUGIN_TYPE_DATA ; 
 scalar_t__ _krb5_plugin_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct krb5_plugin**) ; 
 int /*<<< orphan*/  _krb5_plugin_free (struct krb5_plugin*) ; 
 struct krb5_plugin* _krb5_plugin_get_next (struct krb5_plugin*) ; 
 TYPE_1__* _krb5_plugin_get_symbol (struct krb5_plugin*) ; 
 int /*<<< orphan*/  krb5_set_error_message (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  windcctx ; 
 TYPE_1__* windcft ; 

krb5_error_code
krb5_kdc_windc_init(krb5_context context)
{
    struct krb5_plugin *list = NULL, *e;
    krb5_error_code ret;

    ret = _krb5_plugin_find(context, PLUGIN_TYPE_DATA, "windc", &list);
    if(ret != 0 || list == NULL)
	return 0;

    for (e = list; e != NULL; e = _krb5_plugin_get_next(e)) {

	windcft = _krb5_plugin_get_symbol(e);
	if (windcft->minor_version < KRB5_WINDC_PLUGIN_MINOR)
	    continue;

	(*windcft->init)(context, &windcctx);
	break;
    }
    _krb5_plugin_free(list);
    if (e == NULL) {
	krb5_set_error_message(context, ENOENT, "Did not find any WINDC plugin");
	windcft = NULL;
	return ENOENT;
    }

    return 0;
}
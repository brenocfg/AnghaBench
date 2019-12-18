#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct krb5_plugin {int dummy; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
struct TYPE_4__ {scalar_t__ version; } ;
typedef  TYPE_1__ krb5_cc_ops ;

/* Variables and functions */
 scalar_t__ KRB5_CC_OPS_VERSION ; 
 int /*<<< orphan*/  KRB5_PLUGIN_CCACHE ; 
 int /*<<< orphan*/  PLUGIN_TYPE_DATA ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _krb5_plugin_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct krb5_plugin**) ; 
 int /*<<< orphan*/  _krb5_plugin_free (struct krb5_plugin*) ; 
 struct krb5_plugin* _krb5_plugin_get_next (struct krb5_plugin*) ; 
 TYPE_1__* _krb5_plugin_get_symbol (struct krb5_plugin*) ; 
 scalar_t__ krb5_cc_register (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

krb5_error_code
_krb5_load_ccache_plugins(krb5_context context)
{
    struct krb5_plugin * plist = NULL;
    struct krb5_plugin *p;
    krb5_error_code code;

    code = _krb5_plugin_find(context, PLUGIN_TYPE_DATA, KRB5_PLUGIN_CCACHE,
                             &plist);
    if (code)
        return code;

    for (p = plist; p != NULL; p = _krb5_plugin_get_next(p)) {
        krb5_cc_ops * ccops;
        krb5_error_code c_load;

        ccops = _krb5_plugin_get_symbol(p);
        if (ccops != NULL && ccops->version == KRB5_CC_OPS_VERSION) {
            c_load = krb5_cc_register(context, ccops, TRUE);
            if (c_load != 0)
                code = c_load;
        }
    }

    _krb5_plugin_free(plist);

    return code;
}
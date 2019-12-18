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
struct iter_ctx {char const* name; int min_version; int /*<<< orphan*/  ret; int /*<<< orphan*/ * n; int /*<<< orphan*/ * result; void* userctx; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,void const*,void*,void*) ;int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/ * heim_string_t ;
typedef  int /*<<< orphan*/ * heim_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_MUTEX_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEIMDAL_MUTEX_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KRB5_PLUGIN_NO_HANDLE ; 
 int /*<<< orphan*/  eval_results ; 
 int /*<<< orphan*/ * heim_array_create () ; 
 int /*<<< orphan*/  heim_array_iterate_f (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct iter_ctx*) ; 
 int /*<<< orphan*/ * heim_dict_copy_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heim_dict_iterate_f (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct iter_ctx*) ; 
 int /*<<< orphan*/  heim_release (int /*<<< orphan*/ *) ; 
 void* heim_string_create (char const*) ; 
 int /*<<< orphan*/  modules ; 
 int /*<<< orphan*/  plugin_mutex ; 
 int /*<<< orphan*/  search_modules ; 

krb5_error_code
_krb5_plugin_run_f(krb5_context context,
		   const char *module,
		   const char *name,
		   int min_version,
		   int flags,
		   void *userctx,
		   krb5_error_code (*func)(krb5_context, const void *, void *, void *))
{
    heim_string_t m = heim_string_create(module);
    heim_dict_t dict;
    struct iter_ctx s;

    HEIMDAL_MUTEX_lock(&plugin_mutex);

    dict = heim_dict_copy_value(modules, m);
    heim_release(m);
    if (dict == NULL) {
	HEIMDAL_MUTEX_unlock(&plugin_mutex);
	return KRB5_PLUGIN_NO_HANDLE;
    }

    s.context = context;
    s.name = name;
    s.n = heim_string_create(name);
    s.min_version = min_version;
    s.result = heim_array_create();
    s.func = func;
    s.userctx = userctx;

    heim_dict_iterate_f(dict, search_modules, &s);

    heim_release(dict);

    HEIMDAL_MUTEX_unlock(&plugin_mutex);

    s.ret = KRB5_PLUGIN_NO_HANDLE;

    heim_array_iterate_f(s.result, eval_results, &s);

    heim_release(s.result);
    heim_release(s.n);

    return s.ret;
}
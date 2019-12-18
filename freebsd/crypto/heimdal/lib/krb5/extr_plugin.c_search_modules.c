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
struct plugin2 {int /*<<< orphan*/  names; int /*<<< orphan*/ * dsohandle; } ;
struct plug {struct common_plugin_method* dataptr; int /*<<< orphan*/  ctx; } ;
struct iter_ctx {scalar_t__ min_version; int /*<<< orphan*/  result; int /*<<< orphan*/  n; int /*<<< orphan*/  context; int /*<<< orphan*/  name; } ;
struct common_plugin_method {int (* init ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ version; } ;
typedef  struct plugin2* heim_object_t ;

/* Variables and functions */
 struct common_plugin_method* dlsym (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct plug* heim_alloc (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heim_array_append_value (int /*<<< orphan*/ ,struct plug*) ; 
 int /*<<< orphan*/  heim_dict_add_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct plug*) ; 
 struct plug* heim_dict_copy_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heim_release (struct plug*) ; 
 int /*<<< orphan*/  plug_free ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
search_modules(void *ctx, heim_object_t key, heim_object_t value)
{
    struct iter_ctx *s = ctx;
    struct plugin2 *p = value;
    struct plug *pl = heim_dict_copy_value(p->names, s->n);
    struct common_plugin_method *cpm;

    if (pl == NULL) {
	if (p->dsohandle == NULL)
	    return;

	pl = heim_alloc(sizeof(*pl), "struct-plug", plug_free);

	cpm = pl->dataptr = dlsym(p->dsohandle, s->name);
	if (cpm) {
	    int ret;

	    ret = cpm->init(s->context, &pl->ctx);
	    if (ret)
		cpm = pl->dataptr = NULL;
	}
	heim_dict_add_value(p->names, s->n, pl);
    } else {
	cpm = pl->dataptr;
    }

    if (cpm && cpm->version >= s->min_version)
	heim_array_append_value(s->result, pl);

    heim_release(pl);
}
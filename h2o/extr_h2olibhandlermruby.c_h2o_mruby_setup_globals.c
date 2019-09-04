#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * exc; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_ROOT ; 
 char* H2O_TO_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  h2o_fatal (char*,char const*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  h2o_mruby_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_mruby_eval_expr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  h2o_mruby_new_str (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_class_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_gv_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_inspect (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_1__*,char*) ; 
 scalar_t__ mrb_obj_is_instance_of (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void h2o_mruby_setup_globals(mrb_state *mrb)
{
    const char *root = getenv("H2O_ROOT");
    if (root == NULL)
        root = H2O_TO_STR(H2O_ROOT);
    mrb_gv_set(mrb, mrb_intern_lit(mrb, "$H2O_ROOT"), h2o_mruby_new_str(mrb, root, strlen(root)));

    h2o_mruby_eval_expr(mrb, "$LOAD_PATH << \"#{$H2O_ROOT}/share/h2o/mruby\"");
    h2o_mruby_assert(mrb);

    /* require core modules and include built-in libraries */
    h2o_mruby_eval_expr(mrb, "require \"#{$H2O_ROOT}/share/h2o/mruby/preloads.rb\"");
    if (mrb->exc != NULL) {
        const char *msg = "";
        if (mrb_obj_is_instance_of(mrb, mrb_obj_value(mrb->exc), mrb_class_get(mrb, "LoadError"))) {
            msg = "Did you forget to run `make install`?\n";
        }
        h2o_fatal("an error occurred while loading %s/%s: %s\n%s", root, "share/h2o/mruby/preloads.rb",
                  RSTRING_PTR(mrb_inspect(mrb, mrb_obj_value(mrb->exc))), msg);
    }
}
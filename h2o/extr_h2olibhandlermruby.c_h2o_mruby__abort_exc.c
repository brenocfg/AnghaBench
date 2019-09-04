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
struct TYPE_4__ {int /*<<< orphan*/  exc; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o__fatal (char const*,int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_inspect (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 

void h2o_mruby__abort_exc(mrb_state *mrb, const char *mess, const char *file, int line)
{
    h2o__fatal(file, line, "%s:%s\n", mess, RSTRING_PTR(mrb_inspect(mrb, mrb_obj_value(mrb->exc))));
}
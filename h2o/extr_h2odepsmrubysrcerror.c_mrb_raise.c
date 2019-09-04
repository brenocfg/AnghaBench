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
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_exc_new_str (int /*<<< orphan*/ *,struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_exc_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char const*) ; 

void
mrb_raise(mrb_state *mrb, struct RClass *c, const char *msg)
{
  mrb_exc_raise(mrb, mrb_exc_new_str(mrb, c, mrb_str_new_cstr(mrb, msg)));
}
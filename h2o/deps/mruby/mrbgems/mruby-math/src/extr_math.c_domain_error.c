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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 struct RClass* mrb_class_get_under (int /*<<< orphan*/ *,struct RClass*,char*) ; 
 struct RClass* mrb_module_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
domain_error(mrb_state *mrb, const char *func)
{
  struct RClass *math = mrb_module_get(mrb, "Math");
  struct RClass *domainerror = mrb_class_get_under(mrb, math, "DomainError");
  mrb_value str = mrb_str_new_cstr(mrb, func);
  mrb_raisef(mrb, domainerror, "Numerical argument is out of domain - %S", str);
}
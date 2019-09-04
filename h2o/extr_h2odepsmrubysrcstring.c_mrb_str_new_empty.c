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
struct RString {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_obj_value (struct RString*) ; 
 struct RString* str_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_with_class (int /*<<< orphan*/ *,struct RString*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_str_new_empty(mrb_state *mrb, mrb_value str)
{
  struct RString *s = str_new(mrb, 0, 0);

  str_with_class(mrb, s, str);
  return mrb_obj_value(s);
}
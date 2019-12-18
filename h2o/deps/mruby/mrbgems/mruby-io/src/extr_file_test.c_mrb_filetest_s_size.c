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
struct stat {int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 

mrb_value
mrb_filetest_s_size(mrb_state *mrb, mrb_value klass)
{
  struct stat st;
  mrb_value obj;

  mrb_get_args(mrb, "o", &obj);

  if (mrb_stat(mrb, obj, &st) < 0)
    mrb_sys_fail(mrb, "mrb_stat");

  return mrb_fixnum_value(st.st_size);
}
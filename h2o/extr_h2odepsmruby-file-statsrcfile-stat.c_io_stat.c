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
struct stat {int dummy; } ;
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  Data_Wrap_Struct (int /*<<< orphan*/ *,struct RClass*,int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  E_NOTIMP_ERROR ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 struct RClass* mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 struct RClass* mrb_class_get_under (int /*<<< orphan*/ *,struct RClass*,char*) ; 
 int /*<<< orphan*/  mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mrb_respond_to (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stat* mrb_stat_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_stat_type ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static mrb_value
io_stat(mrb_state *mrb, mrb_value self)
{
  struct RClass *file_class;
  struct RClass *stat_class;
  struct stat st, *ptr;
  mrb_value fileno;

  if (mrb_respond_to(mrb, self, mrb_intern_lit(mrb, "fileno"))) {
    fileno = mrb_funcall(mrb, self, "fileno", 0);
  }
  else {
    mrb_raise(mrb, E_NOTIMP_ERROR, "`fileno' is not implemented");
  }

  if (fstat(mrb_fixnum(fileno), &st) == -1) {
    mrb_sys_fail(mrb, "fstat");
  }

  file_class = mrb_class_get(mrb, "File");
  stat_class = mrb_class_get_under(mrb, file_class, "Stat");
  ptr = mrb_stat_alloc(mrb);
  *ptr = st;

  return mrb_obj_value(Data_Wrap_Struct(mrb, stat_class, &mrb_stat_type, ptr));
}
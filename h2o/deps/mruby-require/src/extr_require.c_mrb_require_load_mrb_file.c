#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_8__ {scalar_t__ jmp; scalar_t__ exc; } ;
typedef  TYPE_1__ mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;
typedef  int /*<<< orphan*/  jmp_buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  E_LOAD_ERROR ; 
 int /*<<< orphan*/  eval_load_irep (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_get_args (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raisef (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mrb_read_irep_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* mrb_str_to_cstr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_true_value () ; 

__attribute__((used)) static mrb_value
mrb_require_load_mrb_file(mrb_state *mrb, mrb_value self)
{
  char *path_ptr = NULL;
  FILE *fp = NULL;
  mrb_irep *irep;
  mrb_value path;

  mrb_get_args(mrb, "S", &path);
  path_ptr = mrb_str_to_cstr(mrb, path);

  fp = fopen(path_ptr, "rb");
  if (fp == NULL) {
    mrb_raisef(mrb, E_LOAD_ERROR, "can't open file -- %S", path);
  }

  irep = mrb_read_irep_file(mrb, fp);
  fclose(fp);

  if (irep) {
    eval_load_irep(mrb, irep);
  } else if (mrb->exc) {
    // fail to load
    longjmp(*(jmp_buf*)mrb->jmp, 1);
  } else {
    mrb_raisef(mrb, E_LOAD_ERROR, "can't load file -- %S", path);
    return mrb_nil_value();
  }

  return mrb_true_value();
}
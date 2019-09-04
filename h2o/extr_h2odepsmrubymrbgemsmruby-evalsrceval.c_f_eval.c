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
struct RProc {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_PROC_CFUNC_P (struct RProc*) ; 
 struct RProc* create_proc_from_string (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  exec_irep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct RProc*) ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,char**,int*,int /*<<< orphan*/ *,char**,int*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value
f_eval(mrb_state *mrb, mrb_value self)
{
  char *s;
  mrb_int len;
  mrb_value binding = mrb_nil_value();
  char *file = NULL;
  mrb_int line = 1;
  struct RProc *proc;

  mrb_get_args(mrb, "s|ozi", &s, &len, &binding, &file, &line);

  proc = create_proc_from_string(mrb, s, len, binding, file, line);
  mrb_assert(!MRB_PROC_CFUNC_P(proc));
  return exec_irep(mrb, self, proc);
}
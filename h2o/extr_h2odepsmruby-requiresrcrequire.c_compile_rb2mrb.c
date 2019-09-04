#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int no_exec; } ;
typedef  TYPE_2__ mrbc_context ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;
struct TYPE_8__ {int /*<<< orphan*/ * irep; } ;
struct TYPE_10__ {TYPE_1__ body; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MRB_DUMP_GENERAL_FAILURE ; 
 int /*<<< orphan*/  mrb_close (int /*<<< orphan*/ *) ; 
 int mrb_dump_irep_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_load_nstring_cxt (int /*<<< orphan*/ *,char const*,int,TYPE_2__*) ; 
 int /*<<< orphan*/ * mrb_open () ; 
 TYPE_6__* mrb_proc_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_undef_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrbc_context_free (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* mrbc_context_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrbc_filename (int /*<<< orphan*/ *,TYPE_2__*,char const*) ; 

__attribute__((used)) static int
compile_rb2mrb(mrb_state *mrb0, const char *code, int code_len, const char *path, FILE* tmpfp)
{
  mrb_state *mrb = mrb_open();
  mrb_value result;
  mrbc_context *c;
  int ret = -1;
  int debuginfo = 1;
  mrb_irep *irep;

  c = mrbc_context_new(mrb);
  c->no_exec = 1;
  if (path != NULL) {
    mrbc_filename(mrb, c, path);
  }

  result = mrb_load_nstring_cxt(mrb, code, code_len, c);
  if (mrb_undef_p(result)) {
    mrbc_context_free(mrb, c);
    mrb_close(mrb);
    return MRB_DUMP_GENERAL_FAILURE;
  }

  irep = mrb_proc_ptr(result)->body.irep;
  ret = mrb_dump_irep_binary(mrb, irep, debuginfo, tmpfp);

  mrbc_context_free(mrb, c);
  mrb_close(mrb);

  return ret;
}
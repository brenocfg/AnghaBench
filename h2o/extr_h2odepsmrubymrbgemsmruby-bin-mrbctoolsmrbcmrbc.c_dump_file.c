#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mrbc_args {char* initname; char* prog; int /*<<< orphan*/  flags; scalar_t__ remove_lv; } ;
struct TYPE_2__ {int /*<<< orphan*/ * irep; } ;
struct RProc {TYPE_1__ body; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MRB_DUMP_INVALID_ARGUMENT ; 
 int MRB_DUMP_OK ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int mrb_dump_irep_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mrb_dump_irep_cfunc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_irep_remove_lv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
dump_file(mrb_state *mrb, FILE *wfp, const char *outfile, struct RProc *proc, struct mrbc_args *args)
{
  int n = MRB_DUMP_OK;
  mrb_irep *irep = proc->body.irep;

  if (args->remove_lv) {
    mrb_irep_remove_lv(mrb, irep);
  }
  if (args->initname) {
    n = mrb_dump_irep_cfunc(mrb, irep, args->flags, wfp, args->initname);
    if (n == MRB_DUMP_INVALID_ARGUMENT) {
      fprintf(stderr, "%s: invalid C language symbol name\n", args->initname);
    }
  }
  else {
    n = mrb_dump_irep_binary(mrb, irep, args->flags, wfp);
  }
  if (n != MRB_DUMP_OK) {
    fprintf(stderr, "%s: error in mrb dump (%s) %d\n", args->prog, outfile, n);
  }
  return n;
}
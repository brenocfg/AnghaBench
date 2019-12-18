#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* filename; int lineno; int /*<<< orphan*/  jmp; int /*<<< orphan*/  mpool; int /*<<< orphan*/  iseq; int /*<<< orphan*/  mrb; struct TYPE_3__* prev; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_THROW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_pool_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
codegen_error(codegen_scope *s, const char *message)
{
  if (!s) return;
  while (s->prev) {
    codegen_scope *tmp = s->prev;
    mrb_free(s->mrb, s->iseq);
    mrb_pool_close(s->mpool);
    s = tmp;
  }
#ifndef MRB_DISABLE_STDIO
  if (s->filename && s->lineno) {
    fprintf(stderr, "codegen error:%s:%d: %s\n", s->filename, s->lineno, message);
  }
  else {
    fprintf(stderr, "codegen error: %s\n", message);
  }
#endif
  MRB_THROW(&s->jmp);
}
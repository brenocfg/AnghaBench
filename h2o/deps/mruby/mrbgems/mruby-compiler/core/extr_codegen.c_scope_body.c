#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  cdr; int /*<<< orphan*/  car; } ;
typedef  TYPE_2__ node ;
struct TYPE_15__ {TYPE_1__* irep; int /*<<< orphan*/  iseq; scalar_t__ sp; int /*<<< orphan*/  mrb; } ;
typedef  TYPE_3__ codegen_scope ;
struct TYPE_13__ {int rlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_RETURN ; 
 int /*<<< orphan*/  OP_STOP ; 
 int /*<<< orphan*/  VAL ; 
 int /*<<< orphan*/  codegen (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  codegen_error (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  gen_return (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  genop_0 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scope_finish (TYPE_3__*) ; 
 TYPE_3__* scope_new (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
scope_body(codegen_scope *s, node *tree, int val)
{
  codegen_scope *scope = scope_new(s->mrb, s, tree->car);
  if (scope == NULL) {
    codegen_error(s, "unexpected scope");
  }

  codegen(scope, tree->cdr, VAL);
  gen_return(scope, OP_RETURN, scope->sp-1);
  if (!s->iseq) {
    genop_0(scope, OP_STOP);
  }
  scope_finish(scope);
  if (!s->irep) {
    /* should not happen */
    return 0;
  }
  return s->irep->rlen - 1;
}
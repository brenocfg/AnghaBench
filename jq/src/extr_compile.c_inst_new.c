#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  opcode ;
struct TYPE_4__ {int bytecode_pos; int nformals; int nactuals; scalar_t__ locfile; int /*<<< orphan*/  source; void* arglist; void* subfn; scalar_t__ referenced; scalar_t__ any_unbound; scalar_t__ symbol; scalar_t__ bound_by; int /*<<< orphan*/  op; scalar_t__ prev; scalar_t__ next; } ;
typedef  TYPE_1__ inst ;

/* Variables and functions */
 int /*<<< orphan*/  UNKNOWN_LOCATION ; 
 void* gen_noop () ; 
 TYPE_1__* jv_mem_alloc (int) ; 

__attribute__((used)) static inst* inst_new(opcode op) {
  inst* i = jv_mem_alloc(sizeof(inst));
  i->next = i->prev = 0;
  i->op = op;
  i->bytecode_pos = -1;
  i->bound_by = 0;
  i->symbol = 0;
  i->any_unbound = 0;
  i->referenced = 0;
  i->nformals = -1;
  i->nactuals = -1;
  i->subfn = gen_noop();
  i->arglist = gen_noop();
  i->source = UNKNOWN_LOCATION;
  i->locfile = 0;
  return i;
}
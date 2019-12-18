#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cfunction {scalar_t__ nargs; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {struct cfunction const* cfunc; } ;
struct TYPE_6__ {scalar_t__ any_unbound; scalar_t__ nformals; int /*<<< orphan*/  symbol; TYPE_1__ imm; } ;
typedef  TYPE_2__ inst ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLOSURE_CREATE_C ; 
 int /*<<< orphan*/  inst_block (TYPE_2__*) ; 
 TYPE_2__* inst_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 

block gen_cbinding(const struct cfunction* cfunctions, int ncfunctions, block code) {
  for (int cfunc=0; cfunc<ncfunctions; cfunc++) {
    inst* i = inst_new(CLOSURE_CREATE_C);
    i->imm.cfunc = &cfunctions[cfunc];
    i->symbol = strdup(cfunctions[cfunc].name);
    i->nformals = cfunctions[cfunc].nargs - 1;
    i->any_unbound = 0;
    code = BLOCK(inst_block(i), code);
  }
  return code;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  constant; } ;
struct inst {TYPE_1__ imm; int /*<<< orphan*/  op; scalar_t__ locfile; int /*<<< orphan*/  arglist; int /*<<< orphan*/  subfn; struct inst* symbol; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int OP_HAS_CONSTANT ; 
 int /*<<< orphan*/  block_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_mem_free (struct inst*) ; 
 int /*<<< orphan*/  locfile_free (scalar_t__) ; 
 TYPE_2__* opcode_describe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inst_free(struct inst* i) {
  jv_mem_free(i->symbol);
  block_free(i->subfn);
  block_free(i->arglist);
  if (i->locfile)
    locfile_free(i->locfile);
  if (opcode_describe(i->op)->flags & OP_HAS_CONSTANT) {
    jv_free(i->imm.constant);
  }
  jv_mem_free(i);
}
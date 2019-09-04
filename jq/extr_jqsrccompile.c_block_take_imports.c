#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jv ;
struct TYPE_12__ {int /*<<< orphan*/  constant; } ;
struct TYPE_13__ {scalar_t__ op; TYPE_3__ imm; } ;
typedef  TYPE_4__ inst ;
struct TYPE_14__ {TYPE_2__* first; } ;
typedef  TYPE_5__ block ;
struct TYPE_11__ {scalar_t__ op; TYPE_1__* next; } ;
struct TYPE_10__ {scalar_t__ op; } ;

/* Variables and functions */
 scalar_t__ DEPS ; 
 scalar_t__ MODULEMETA ; 
 scalar_t__ TOP ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* block_take (TYPE_5__*) ; 
 int /*<<< orphan*/  inst_free (TYPE_4__*) ; 
 int /*<<< orphan*/  jv_array () ; 
 int /*<<< orphan*/  jv_array_append (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 

jv block_take_imports(block* body) {
  jv imports = jv_array();

  /* Parser should never generate TOP before imports */
  assert(!(body->first && body->first->op == TOP && body->first->next &&
        (body->first->next->op == MODULEMETA || body->first->next->op == DEPS)));

  while (body->first && (body->first->op == MODULEMETA || body->first->op == DEPS)) {
    inst* dep = block_take(body);
    if (dep->op == DEPS) {
      imports = jv_array_append(imports, jv_copy(dep->imm.constant));
    }
    inst_free(dep);
  }
  return imports;
}
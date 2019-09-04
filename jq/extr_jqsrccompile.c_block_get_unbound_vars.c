#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jv ;
struct TYPE_5__ {TYPE_1__* first; } ;
struct TYPE_4__ {scalar_t__ op; int /*<<< orphan*/  symbol; int /*<<< orphan*/ * bound_by; TYPE_2__ subfn; struct TYPE_4__* next; } ;
typedef  TYPE_1__ inst ;
typedef  TYPE_2__ block ;

/* Variables and functions */
 scalar_t__ JV_KIND_OBJECT ; 
 scalar_t__ STOREV ; 
 scalar_t__ STOREVN ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_object_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_true () ; 

__attribute__((used)) static void block_get_unbound_vars(block b, jv *vars) {
  assert(vars != NULL);
  assert(jv_get_kind(*vars) == JV_KIND_OBJECT);
  for (inst* i = b.first; i; i = i->next) {
    if (i->subfn.first) {
      block_get_unbound_vars(i->subfn, vars);
      continue;
    }
    if ((i->op == STOREV || i->op == STOREVN) && i->bound_by == NULL) {
      *vars = jv_object_set(*vars, jv_string(i->symbol), jv_true());
    }
  }
}
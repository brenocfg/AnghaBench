#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ op; int /*<<< orphan*/  bound_by; struct TYPE_11__* next; } ;
typedef  TYPE_1__ inst ;
struct TYPE_12__ {TYPE_1__* first; } ;
typedef  TYPE_2__ block ;

/* Variables and functions */
 TYPE_2__ BLOCK (TYPE_2__,TYPE_2__) ; 
 int /*<<< orphan*/  OP_HAS_VARIABLE ; 
 scalar_t__ STOREV ; 
 scalar_t__ STOREVN ; 
 int /*<<< orphan*/  block_bind_subblock (int /*<<< orphan*/ ,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inst_block (TYPE_1__*) ; 

__attribute__((used)) static block bind_matcher(block matcher, block body) {
  // cannot call block_bind(matcher, body) because that requires
  // block_has_only_binders(matcher), which is not true here as matchers
  // may also contain code to extract the correct elements
  for (inst* i = matcher.first; i; i = i->next) {
    if ((i->op == STOREV || i->op == STOREVN) && !i->bound_by)
      block_bind_subblock(inst_block(i), body, OP_HAS_VARIABLE, 0);
  }
  return BLOCK(matcher, body);
}
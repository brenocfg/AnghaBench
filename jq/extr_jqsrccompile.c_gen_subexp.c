#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jv ;
struct TYPE_16__ {TYPE_1__* first; } ;
typedef  TYPE_2__ block ;
struct TYPE_15__ {scalar_t__ op; } ;

/* Variables and functions */
 TYPE_2__ BLOCK (TYPE_2__,TYPE_2__,TYPE_2__) ; 
 int /*<<< orphan*/  DUP ; 
 scalar_t__ LOADK ; 
 int /*<<< orphan*/  SUBEXP_BEGIN ; 
 int /*<<< orphan*/  SUBEXP_END ; 
 int /*<<< orphan*/  block_const (TYPE_2__) ; 
 int /*<<< orphan*/  block_free (TYPE_2__) ; 
 scalar_t__ block_is_noop (TYPE_2__) ; 
 scalar_t__ block_is_single (TYPE_2__) ; 
 TYPE_2__ gen_op_pushk_under (int /*<<< orphan*/ ) ; 
 TYPE_2__ gen_op_simple (int /*<<< orphan*/ ) ; 

block gen_subexp(block a) {
  if (block_is_noop(a)) {
    return gen_op_simple(DUP);
  }
  if (block_is_single(a) && a.first->op == LOADK) {
    jv c = block_const(a);
    block_free(a);
    return gen_op_pushk_under(c);
  }
  return BLOCK(gen_op_simple(SUBEXP_BEGIN), a, gen_op_simple(SUBEXP_END));
}
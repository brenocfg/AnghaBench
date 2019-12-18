#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DUP ; 
 int /*<<< orphan*/  POP ; 
 int /*<<< orphan*/  gen_condbranch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_op_simple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_subexp (int /*<<< orphan*/ ) ; 

block gen_cond(block cond, block iftrue, block iffalse) {
  return BLOCK(gen_op_simple(DUP), BLOCK(gen_subexp(cond), gen_op_simple(POP)),
               gen_condbranch(BLOCK(gen_op_simple(POP), iftrue),
                              BLOCK(gen_op_simple(POP), iffalse)));
}
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
 int /*<<< orphan*/  BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FORK ; 
 int /*<<< orphan*/  JUMP ; 
 int /*<<< orphan*/  gen_op_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_op_targetlater (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inst_set_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

block gen_both(block a, block b) {
  block jump = gen_op_targetlater(JUMP);
  block fork = gen_op_target(FORK, jump);
  block c = BLOCK(fork, a, jump, b);
  inst_set_target(jump, c);
  return c;
}
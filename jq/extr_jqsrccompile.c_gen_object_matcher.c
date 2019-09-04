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
 int /*<<< orphan*/  DUP ; 
 int /*<<< orphan*/  INDEX ; 
 int /*<<< orphan*/  gen_op_simple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_subexp (int /*<<< orphan*/ ) ; 

block gen_object_matcher(block name, block curr) {
  return BLOCK(gen_op_simple(DUP), gen_subexp(name), gen_op_simple(INDEX),
               curr);
}
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
 int /*<<< orphan*/  BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DUP ; 
 int OP_BIND_WILDCARD ; 
 int OP_HAS_VARIABLE ; 
 int /*<<< orphan*/  STOREV ; 
 int /*<<< orphan*/  block_bind (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_op_simple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_op_unbound (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static block gen_wildvar_binding(block var, const char* name, block body) {
  return BLOCK(gen_op_simple(DUP), var,
               block_bind(gen_op_unbound(STOREV, name),
                          body, OP_HAS_VARIABLE | OP_BIND_WILDCARD));
}
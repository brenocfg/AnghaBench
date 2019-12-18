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
typedef  int /*<<< orphan*/  inst ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OP_HAS_BINDING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ block_bind_subblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_has_only_binders (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * block_take_last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inst_block (int /*<<< orphan*/ *) ; 

block block_bind_referenced(block binder, block body, int bindflags) {
  assert(block_has_only_binders(binder, bindflags));
  bindflags |= OP_HAS_BINDING;

  inst* curr;
  while ((curr = block_take_last(&binder))) {
    block b = inst_block(curr);
    if (block_bind_subblock(b, body, bindflags, 0) == 0) {
      block_free(b);
    } else {
      body = BLOCK(b, body);
    }
  }
  return body;
}
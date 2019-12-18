#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  referenced; struct TYPE_5__* bound_by; } ;
typedef  TYPE_1__ inst ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_mark_referenced (int /*<<< orphan*/ ) ; 
 TYPE_1__* block_take (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_noop () ; 
 int /*<<< orphan*/  inst_block (TYPE_1__*) ; 
 int /*<<< orphan*/  inst_free (TYPE_1__*) ; 

block block_drop_unreferenced(block body) {
  block_mark_referenced(body);

  block refd = gen_noop();
  inst* curr;
  while ((curr = block_take(&body))) {
    if (curr->bound_by == curr && !curr->referenced) {
      inst_free(curr);
    } else {
      refd = BLOCK(refd, inst_block(curr));
    }
  }
  return refd;
}
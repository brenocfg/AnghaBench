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
struct collection_list {int next_aexpr_elt; int /*<<< orphan*/  regs_mask; int /*<<< orphan*/ ** aexpr_list; scalar_t__ next_memrange; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_agent_expr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
clear_collection_list (struct collection_list *list)
{
  int ndx;

  list->next_memrange = 0;
  for (ndx = 0; ndx < list->next_aexpr_elt; ndx++)
    {
      free_agent_expr (list->aexpr_list[ndx]);
      list->aexpr_list[ndx] = NULL;
    }
  list->next_aexpr_elt = 0;
  memset (list->regs_mask, 0, sizeof (list->regs_mask));
}
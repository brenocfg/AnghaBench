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
struct TYPE_5__ {int nodes_len; int* org_indices; TYPE_1__* nodes; } ;
typedef  TYPE_2__ re_dfa_t ;
struct TYPE_4__ {unsigned int constraint; scalar_t__ duplicated; } ;

/* Variables and functions */

__attribute__((used)) static int
search_duplicated_node (const re_dfa_t *dfa, int org_node,
			unsigned int constraint)
{
  int idx;
  for (idx = dfa->nodes_len - 1; dfa->nodes[idx].duplicated && idx > 0; --idx)
    {
      if (org_node == dfa->org_indices[idx]
	  && constraint == dfa->nodes[idx].constraint)
	return idx; /* Found.  */
    }
  return -1; /* Not found.  */
}
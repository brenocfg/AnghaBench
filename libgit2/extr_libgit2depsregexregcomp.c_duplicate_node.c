#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* org_indices; TYPE_3__* nodes; } ;
typedef  TYPE_1__ re_dfa_t ;
struct TYPE_6__ {unsigned int constraint; int duplicated; } ;

/* Variables and functions */
 scalar_t__ BE (int,int) ; 
 int re_dfa_add_node (TYPE_1__*,TYPE_3__) ; 

__attribute__((used)) static int
duplicate_node (re_dfa_t *dfa, int org_idx, unsigned int constraint)
{
  int dup_idx = re_dfa_add_node (dfa, dfa->nodes[org_idx]);
  if (BE (dup_idx != -1, 1))
    {
      dfa->nodes[dup_idx].constraint = constraint;
      dfa->nodes[dup_idx].constraint |= dfa->nodes[org_idx].constraint;
      dfa->nodes[dup_idx].duplicated = 1;

      /* Store the index of the original node.  */
      dfa->org_indices[dup_idx] = org_idx;
    }
  return dup_idx;
}
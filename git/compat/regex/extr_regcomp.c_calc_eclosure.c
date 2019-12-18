#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ reg_errcode_t ;
typedef  int /*<<< orphan*/  re_node_set ;
struct TYPE_6__ {int nodes_len; TYPE_1__* eclosures; } ;
typedef  TYPE_2__ re_dfa_t ;
struct TYPE_5__ {int nelem; } ;

/* Variables and functions */
 scalar_t__ BE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_NOERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ calc_eclosure_iter (int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  re_node_set_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static reg_errcode_t
calc_eclosure (re_dfa_t *dfa)
{
  int node_idx, incomplete;
#ifdef DEBUG
  assert (dfa->nodes_len > 0);
#endif
  incomplete = 0;
  /* For each nodes, calculate epsilon closure.  */
  for (node_idx = 0; ; ++node_idx)
    {
      reg_errcode_t err;
      re_node_set eclosure_elem;
      if (node_idx == dfa->nodes_len)
	{
	  if (!incomplete)
	    break;
	  incomplete = 0;
	  node_idx = 0;
	}

#ifdef DEBUG
      assert (dfa->eclosures[node_idx].nelem != -1);
#endif

      /* If we have already calculated, skip it.  */
      if (dfa->eclosures[node_idx].nelem != 0)
	continue;
      /* Calculate epsilon closure of `node_idx'.  */
      err = calc_eclosure_iter (&eclosure_elem, dfa, node_idx, 1);
      if (BE (err != REG_NOERROR, 0))
	return err;

      if (dfa->eclosures[node_idx].nelem == 0)
	{
	  incomplete = 1;
	  re_node_set_free (&eclosure_elem);
	}
    }
  return REG_NOERROR;
}
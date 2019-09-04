#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ reg_errcode_t ;
struct TYPE_15__ {int nelem; } ;
typedef  TYPE_3__ re_node_set ;
struct TYPE_16__ {TYPE_3__* eclosures; TYPE_2__* edests; TYPE_1__* nodes; } ;
typedef  TYPE_4__ re_dfa_t ;
struct TYPE_14__ {int nelem; size_t* elems; } ;
struct TYPE_13__ {int /*<<< orphan*/  type; scalar_t__ constraint; int /*<<< orphan*/  duplicated; } ;

/* Variables and functions */
 scalar_t__ BE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_EPSILON_NODE (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_ESPACE ; 
 scalar_t__ REG_NOERROR ; 
 scalar_t__ duplicate_node_closure (TYPE_4__*,int,int,int,scalar_t__) ; 
 scalar_t__ re_node_set_alloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  re_node_set_free (TYPE_3__*) ; 
 int re_node_set_insert (TYPE_3__*,int) ; 
 scalar_t__ re_node_set_merge (TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static reg_errcode_t
calc_eclosure_iter (re_node_set *new_set, re_dfa_t *dfa, int node, int root)
{
  reg_errcode_t err;
  int i;
  re_node_set eclosure;
  int ret;
  int incomplete = 0;
  err = re_node_set_alloc (&eclosure, dfa->edests[node].nelem + 1);
  if (BE (err != REG_NOERROR, 0))
    return err;

  /* This indicates that we are calculating this node now.
     We reference this value to avoid infinite loop.  */
  dfa->eclosures[node].nelem = -1;

  /* If the current node has constraints, duplicate all nodes
     since they must inherit the constraints.  */
  if (dfa->nodes[node].constraint
      && dfa->edests[node].nelem
      && !dfa->nodes[dfa->edests[node].elems[0]].duplicated)
    {
      err = duplicate_node_closure (dfa, node, node, node,
				    dfa->nodes[node].constraint);
      if (BE (err != REG_NOERROR, 0))
	return err;
    }

  /* Expand each epsilon destination nodes.  */
  if (IS_EPSILON_NODE(dfa->nodes[node].type))
    for (i = 0; i < dfa->edests[node].nelem; ++i)
      {
	re_node_set eclosure_elem;
	int edest = dfa->edests[node].elems[i];
	/* If calculating the epsilon closure of `edest' is in progress,
	   return intermediate result.  */
	if (dfa->eclosures[edest].nelem == -1)
	  {
	    incomplete = 1;
	    continue;
	  }
	/* If we haven't calculated the epsilon closure of `edest' yet,
	   calculate now. Otherwise use calculated epsilon closure.  */
	if (dfa->eclosures[edest].nelem == 0)
	  {
	    err = calc_eclosure_iter (&eclosure_elem, dfa, edest, 0);
	    if (BE (err != REG_NOERROR, 0))
	      return err;
	  }
	else
	  eclosure_elem = dfa->eclosures[edest];
	/* Merge the epsilon closure of `edest'.  */
	err = re_node_set_merge (&eclosure, &eclosure_elem);
	if (BE (err != REG_NOERROR, 0))
	  return err;
	/* If the epsilon closure of `edest' is incomplete,
	   the epsilon closure of this node is also incomplete.  */
	if (dfa->eclosures[edest].nelem == 0)
	  {
	    incomplete = 1;
	    re_node_set_free (&eclosure_elem);
	  }
      }

  /* An epsilon closure includes itself.  */
  ret = re_node_set_insert (&eclosure, node);
  if (BE (ret < 0, 0))
    return REG_ESPACE;
  if (incomplete && !root)
    dfa->eclosures[node].nelem = 0;
  else
    dfa->eclosures[node] = eclosure;
  *new_set = eclosure;
  return REG_NOERROR;
}
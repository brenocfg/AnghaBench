#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ reg_errcode_t ;
typedef  scalar_t__ re_token_type_t ;
struct TYPE_18__ {scalar_t__ idx; } ;
struct TYPE_21__ {scalar_t__ type; TYPE_3__ opr; } ;
typedef  TYPE_6__ re_token_t ;
struct TYPE_22__ {int nelem; int* elems; } ;
typedef  TYPE_7__ re_node_set ;
struct TYPE_23__ {int init_node; scalar_t__ nbackref; TYPE_5__* init_state; TYPE_5__* init_state_begbuf; TYPE_5__* init_state_nl; TYPE_5__* init_state_word; scalar_t__ eclosures; TYPE_4__* edests; TYPE_6__* nodes; TYPE_2__* str_tree; } ;
typedef  TYPE_8__ re_dfa_t ;
struct TYPE_20__ {scalar_t__ has_constraint; } ;
struct TYPE_19__ {int* elems; } ;
struct TYPE_17__ {TYPE_1__* first; } ;
struct TYPE_16__ {int node_idx; } ;

/* Variables and functions */
 scalar_t__ BE (int,int /*<<< orphan*/ ) ; 
 int CONTEXT_BEGBUF ; 
 int CONTEXT_NEWLINE ; 
 int CONTEXT_WORD ; 
 scalar_t__ OP_BACK_REF ; 
 scalar_t__ OP_CLOSE_SUBEXP ; 
 scalar_t__ REG_NOERROR ; 
 void* re_acquire_state_context (scalar_t__*,TYPE_8__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  re_node_set_contains (TYPE_7__*,int) ; 
 int /*<<< orphan*/  re_node_set_free (TYPE_7__*) ; 
 scalar_t__ re_node_set_init_copy (TYPE_7__*,scalar_t__) ; 
 scalar_t__ re_node_set_merge (TYPE_7__*,scalar_t__) ; 

__attribute__((used)) static reg_errcode_t
create_initial_state (re_dfa_t *dfa)
{
  int first, i;
  reg_errcode_t err;
  re_node_set init_nodes;

  /* Initial states have the epsilon closure of the node which is
     the first node of the regular expression.  */
  first = dfa->str_tree->first->node_idx;
  dfa->init_node = first;
  err = re_node_set_init_copy (&init_nodes, dfa->eclosures + first);
  if (BE (err != REG_NOERROR, 0))
    return err;

  /* The back-references which are in initial states can epsilon transit,
     since in this case all of the subexpressions can be null.
     Then we add epsilon closures of the nodes which are the next nodes of
     the back-references.  */
  if (dfa->nbackref > 0)
    for (i = 0; i < init_nodes.nelem; ++i)
      {
	int node_idx = init_nodes.elems[i];
	re_token_type_t type = dfa->nodes[node_idx].type;

	int clexp_idx;
	if (type != OP_BACK_REF)
	  continue;
	for (clexp_idx = 0; clexp_idx < init_nodes.nelem; ++clexp_idx)
	  {
	    re_token_t *clexp_node;
	    clexp_node = dfa->nodes + init_nodes.elems[clexp_idx];
	    if (clexp_node->type == OP_CLOSE_SUBEXP
		&& clexp_node->opr.idx == dfa->nodes[node_idx].opr.idx)
	      break;
	  }
	if (clexp_idx == init_nodes.nelem)
	  continue;

	if (type == OP_BACK_REF)
	  {
	    int dest_idx = dfa->edests[node_idx].elems[0];
	    if (!re_node_set_contains (&init_nodes, dest_idx))
	      {
		reg_errcode_t err = re_node_set_merge (&init_nodes,
						       dfa->eclosures
						       + dest_idx);
		if (err != REG_NOERROR)
		  return err;
		i = 0;
	      }
	  }
      }

  /* It must be the first time to invoke acquire_state.  */
  dfa->init_state = re_acquire_state_context (&err, dfa, &init_nodes, 0);
  /* We don't check ERR here, since the initial state must not be NULL.  */
  if (BE (dfa->init_state == NULL, 0))
    return err;
  if (dfa->init_state->has_constraint)
    {
      dfa->init_state_word = re_acquire_state_context (&err, dfa, &init_nodes,
						       CONTEXT_WORD);
      dfa->init_state_nl = re_acquire_state_context (&err, dfa, &init_nodes,
						     CONTEXT_NEWLINE);
      dfa->init_state_begbuf = re_acquire_state_context (&err, dfa,
							 &init_nodes,
							 CONTEXT_NEWLINE
							 | CONTEXT_BEGBUF);
      if (BE (dfa->init_state_word == NULL || dfa->init_state_nl == NULL
	      || dfa->init_state_begbuf == NULL, 0))
	return err;
    }
  else
    dfa->init_state_word = dfa->init_state_nl
      = dfa->init_state_begbuf = dfa->init_state;

  re_node_set_free (&init_nodes);
  return REG_NOERROR;
}
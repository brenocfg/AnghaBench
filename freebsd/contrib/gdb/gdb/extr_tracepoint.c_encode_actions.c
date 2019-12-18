#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct tracepoint {int /*<<< orphan*/  address; struct action_line* actions; } ;
struct expression {TYPE_1__* elts; } ;
struct collection_list {int dummy; } ;
struct cmd_list_element {int dummy; } ;
struct cleanup {int dummy; } ;
struct agent_reqs {int max_height; int reg_mask_len; int* reg_mask; int /*<<< orphan*/  min_height; int /*<<< orphan*/  flaw; } ;
struct agent_expr {int dummy; } ;
struct action_line {char* action; struct action_line* next; } ;
struct TYPE_2__ {int opcode; int longconst; int /*<<< orphan*/  symbol; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int NUM_REGS ; 
#define  OP_REGISTER 130 
#define  OP_VAR_VALUE 129 
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  TARGET_VIRTUAL_FRAME_POINTER (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 unsigned long TYPE_LENGTH (int /*<<< orphan*/ ) ; 
#define  UNOP_MEMVAL 128 
 unsigned long VALUE_ADDRESS (struct value*) ; 
 unsigned long VALUE_OFFSET (struct value*) ; 
 int /*<<< orphan*/  add_aexpr (struct collection_list*,struct agent_expr*) ; 
 int /*<<< orphan*/  add_local_symbols (struct collection_list*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  add_memrange (struct collection_list*,int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  add_register (struct collection_list*,int) ; 
 int /*<<< orphan*/  agent_flaw_none ; 
 int /*<<< orphan*/  ax_reqs (struct agent_expr*,struct agent_reqs*) ; 
 int /*<<< orphan*/  block_for_pc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_collection_list (struct collection_list*) ; 
 scalar_t__ cmd_cfunc_eq (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdlist ; 
 int /*<<< orphan*/  collect_pseudocommand ; 
 int /*<<< orphan*/  collect_symbol (struct collection_list*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  end_actions_pseudocommand ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct value* evaluate_expression (struct expression*) ; 
 int /*<<< orphan*/  free_current_contents ; 
 struct agent_expr* gen_trace_for_expr (int /*<<< orphan*/ ,struct expression*) ; 
 int /*<<< orphan*/  info_verbose ; 
 scalar_t__ isspace (int) ; 
 struct cmd_list_element* lookup_cmd (char**,int /*<<< orphan*/ ,char*,int,int) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct expression**) ; 
 struct cleanup* make_cleanup_free_agent_expr (struct agent_expr*) ; 
 int /*<<< orphan*/  memrange_sortmerge (struct collection_list*) ; 
 struct expression* parse_exp_1 (char**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 struct collection_list stepping_list ; 
 char* strchr (char*,char) ; 
 char** stringify_collection_list (struct collection_list*,char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 struct collection_list tracepoint_list ; 
 int /*<<< orphan*/  while_stepping_pseudocommand ; 

__attribute__((used)) static void
encode_actions (struct tracepoint *t, char ***tdp_actions,
		char ***stepping_actions)
{
  static char tdp_buff[2048], step_buff[2048];
  char *action_exp;
  struct expression *exp = NULL;
  struct action_line *action;
  int i;
  struct value *tempval;
  struct collection_list *collect;
  struct cmd_list_element *cmd;
  struct agent_expr *aexpr;
  int frame_reg;
  LONGEST frame_offset;


  clear_collection_list (&tracepoint_list);
  clear_collection_list (&stepping_list);
  collect = &tracepoint_list;

  *tdp_actions = NULL;
  *stepping_actions = NULL;

  TARGET_VIRTUAL_FRAME_POINTER (t->address, &frame_reg, &frame_offset);

  for (action = t->actions; action; action = action->next)
    {
      QUIT;			/* allow user to bail out with ^C */
      action_exp = action->action;
      while (isspace ((int) *action_exp))
	action_exp++;

      if (*action_exp == '#')	/* comment line */
	return;

      cmd = lookup_cmd (&action_exp, cmdlist, "", -1, 1);
      if (cmd == 0)
	error ("Bad action list item: %s", action_exp);

      if (cmd_cfunc_eq (cmd, collect_pseudocommand))
	{
	  do
	    {			/* repeat over a comma-separated list */
	      QUIT;		/* allow user to bail out with ^C */
	      while (isspace ((int) *action_exp))
		action_exp++;

	      if (0 == strncasecmp ("$reg", action_exp, 4))
		{
		  for (i = 0; i < NUM_REGS; i++)
		    add_register (collect, i);
		  action_exp = strchr (action_exp, ',');	/* more? */
		}
	      else if (0 == strncasecmp ("$arg", action_exp, 4))
		{
		  add_local_symbols (collect,
				     t->address,
				     frame_reg,
				     frame_offset,
				     'A');
		  action_exp = strchr (action_exp, ',');	/* more? */
		}
	      else if (0 == strncasecmp ("$loc", action_exp, 4))
		{
		  add_local_symbols (collect,
				     t->address,
				     frame_reg,
				     frame_offset,
				     'L');
		  action_exp = strchr (action_exp, ',');	/* more? */
		}
	      else
		{
		  unsigned long addr, len;
		  struct cleanup *old_chain = NULL;
		  struct cleanup *old_chain1 = NULL;
		  struct agent_reqs areqs;

		  exp = parse_exp_1 (&action_exp, 
				     block_for_pc (t->address), 1);
		  old_chain = make_cleanup (free_current_contents, &exp);

		  switch (exp->elts[0].opcode)
		    {
		    case OP_REGISTER:
		      i = exp->elts[1].longconst;
		      if (info_verbose)
			printf_filtered ("OP_REGISTER: ");
		      add_register (collect, i);
		      break;

		    case UNOP_MEMVAL:
		      /* safe because we know it's a simple expression */
		      tempval = evaluate_expression (exp);
		      addr = VALUE_ADDRESS (tempval) + VALUE_OFFSET (tempval);
		      len = TYPE_LENGTH (check_typedef (exp->elts[1].type));
		      add_memrange (collect, -1, addr, len);
		      break;

		    case OP_VAR_VALUE:
		      collect_symbol (collect,
				      exp->elts[2].symbol,
				      frame_reg,
				      frame_offset);
		      break;

		    default:	/* full-fledged expression */
		      aexpr = gen_trace_for_expr (t->address, exp);

		      old_chain1 = make_cleanup_free_agent_expr (aexpr);

		      ax_reqs (aexpr, &areqs);
		      if (areqs.flaw != agent_flaw_none)
			error ("malformed expression");

		      if (areqs.min_height < 0)
			error ("gdb: Internal error: expression has min height < 0");
		      if (areqs.max_height > 20)
			error ("expression too complicated, try simplifying");

		      discard_cleanups (old_chain1);
		      add_aexpr (collect, aexpr);

		      /* take care of the registers */
		      if (areqs.reg_mask_len > 0)
			{
			  int ndx1;
			  int ndx2;

			  for (ndx1 = 0; ndx1 < areqs.reg_mask_len; ndx1++)
			    {
			      QUIT;	/* allow user to bail out with ^C */
			      if (areqs.reg_mask[ndx1] != 0)
				{
				  /* assume chars have 8 bits */
				  for (ndx2 = 0; ndx2 < 8; ndx2++)
				    if (areqs.reg_mask[ndx1] & (1 << ndx2))
				      /* it's used -- record it */
				      add_register (collect, ndx1 * 8 + ndx2);
				}
			    }
			}
		      break;
		    }		/* switch */
		  do_cleanups (old_chain);
		}		/* do */
	    }
	  while (action_exp && *action_exp++ == ',');
	}			/* if */
      else if (cmd_cfunc_eq (cmd, while_stepping_pseudocommand))
	{
	  collect = &stepping_list;
	}
      else if (cmd_cfunc_eq (cmd, end_actions_pseudocommand))
	{
	  if (collect == &stepping_list)	/* end stepping actions */
	    collect = &tracepoint_list;
	  else
	    break;		/* end tracepoint actions */
	}
    }				/* for */
  memrange_sortmerge (&tracepoint_list);
  memrange_sortmerge (&stepping_list);

  *tdp_actions = stringify_collection_list (&tracepoint_list, tdp_buff);
  *stepping_actions = stringify_collection_list (&stepping_list, step_buff);
}
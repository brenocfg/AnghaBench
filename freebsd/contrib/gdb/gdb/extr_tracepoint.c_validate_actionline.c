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
struct tracepoint {int /*<<< orphan*/  step_count; int /*<<< orphan*/  address; } ;
struct expression {TYPE_1__* elts; } ;
struct cmd_list_element {int dummy; } ;
struct cleanup {int dummy; } ;
struct agent_reqs {scalar_t__ flaw; scalar_t__ min_height; int max_height; struct expression** reg_mask; } ;
struct agent_expr {scalar_t__ len; } ;
typedef  enum actionline_type { ____Placeholder_actionline_type } actionline_type ;
struct TYPE_2__ {scalar_t__ opcode; int /*<<< orphan*/  symbol; } ;

/* Variables and functions */
 int BADLINE ; 
 char* DEPRECATED_SYMBOL_NAME (int /*<<< orphan*/ ) ; 
 int END ; 
 int GENERIC ; 
 scalar_t__ LOC_CONST ; 
 scalar_t__ LOC_OPTIMIZED_OUT ; 
 scalar_t__ MAX_AGENT_EXPR_LEN ; 
 scalar_t__ OP_VAR_VALUE ; 
 int /*<<< orphan*/  QUIT ; 
 int STEPPING ; 
 scalar_t__ SYMBOL_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMBOL_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ agent_flaw_none ; 
 int /*<<< orphan*/  ax_reqs (struct agent_expr*,struct agent_reqs*) ; 
 int /*<<< orphan*/  block_for_pc (int /*<<< orphan*/ ) ; 
 scalar_t__ cmd_cfunc_eq (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdlist ; 
 int /*<<< orphan*/  collect_pseudocommand ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  end_actions_pseudocommand ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  free_current_contents ; 
 struct agent_expr* gen_trace_for_expr (int /*<<< orphan*/ ,struct expression*) ; 
 scalar_t__ isspace (int) ; 
 struct cmd_list_element* lookup_cmd (char**,int /*<<< orphan*/ ,char*,int,int) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct expression**) ; 
 int /*<<< orphan*/  make_cleanup_free_agent_expr (struct agent_expr*) ; 
 struct expression* parse_exp_1 (char**,int /*<<< orphan*/ ,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,char*,...) ; 
 int /*<<< orphan*/  while_stepping_pseudocommand ; 
 int /*<<< orphan*/  xfree ; 

enum actionline_type
validate_actionline (char **line, struct tracepoint *t)
{
  struct cmd_list_element *c;
  struct expression *exp = NULL;
  struct cleanup *old_chain = NULL;
  char *p;

  /* if EOF is typed, *line is NULL */
  if (*line == NULL)
    return END;

  for (p = *line; isspace ((int) *p);)
    p++;

  /* symbol lookup etc. */
  if (*p == '\0')		/* empty line: just prompt for another line. */
    return BADLINE;

  if (*p == '#')		/* comment line */
    return GENERIC;

  c = lookup_cmd (&p, cmdlist, "", -1, 1);
  if (c == 0)
    {
      warning ("'%s' is not an action that I know, or is ambiguous.", p);
      return BADLINE;
    }

  if (cmd_cfunc_eq (c, collect_pseudocommand))
    {
      struct agent_expr *aexpr;
      struct agent_reqs areqs;

      do
	{			/* repeat over a comma-separated list */
	  QUIT;			/* allow user to bail out with ^C */
	  while (isspace ((int) *p))
	    p++;

	  if (*p == '$')	/* look for special pseudo-symbols */
	    {
	      if ((0 == strncasecmp ("reg", p + 1, 3)) ||
		  (0 == strncasecmp ("arg", p + 1, 3)) ||
		  (0 == strncasecmp ("loc", p + 1, 3)))
		{
		  p = strchr (p, ',');
		  continue;
		}
	      /* else fall thru, treat p as an expression and parse it! */
	    }
	  exp = parse_exp_1 (&p, block_for_pc (t->address), 1);
	  old_chain = make_cleanup (free_current_contents, &exp);

	  if (exp->elts[0].opcode == OP_VAR_VALUE)
	    {
	      if (SYMBOL_CLASS (exp->elts[2].symbol) == LOC_CONST)
		{
		  warning ("constant %s (value %ld) will not be collected.",
			   DEPRECATED_SYMBOL_NAME (exp->elts[2].symbol),
			   SYMBOL_VALUE (exp->elts[2].symbol));
		  return BADLINE;
		}
	      else if (SYMBOL_CLASS (exp->elts[2].symbol) == LOC_OPTIMIZED_OUT)
		{
		  warning ("%s is optimized away and cannot be collected.",
			   DEPRECATED_SYMBOL_NAME (exp->elts[2].symbol));
		  return BADLINE;
		}
	    }

	  /* we have something to collect, make sure that the expr to
	     bytecode translator can handle it and that it's not too long */
	  aexpr = gen_trace_for_expr (t->address, exp);
	  make_cleanup_free_agent_expr (aexpr);

	  if (aexpr->len > MAX_AGENT_EXPR_LEN)
	    error ("expression too complicated, try simplifying");

	  ax_reqs (aexpr, &areqs);
	  (void) make_cleanup (xfree, areqs.reg_mask);

	  if (areqs.flaw != agent_flaw_none)
	    error ("malformed expression");

	  if (areqs.min_height < 0)
	    error ("gdb: Internal error: expression has min height < 0");

	  if (areqs.max_height > 20)
	    error ("expression too complicated, try simplifying");

	  do_cleanups (old_chain);
	}
      while (p && *p++ == ',');
      return GENERIC;
    }
  else if (cmd_cfunc_eq (c, while_stepping_pseudocommand))
    {
      char *steparg;		/* in case warning is necessary */

      while (isspace ((int) *p))
	p++;
      steparg = p;

      if (*p == '\0' ||
	  (t->step_count = strtol (p, &p, 0)) == 0)
	{
	  warning ("'%s': bad step-count; command ignored.", *line);
	  return BADLINE;
	}
      return STEPPING;
    }
  else if (cmd_cfunc_eq (c, end_actions_pseudocommand))
    return END;
  else
    {
      warning ("'%s' is not a supported tracepoint action.", *line);
      return BADLINE;
    }
}
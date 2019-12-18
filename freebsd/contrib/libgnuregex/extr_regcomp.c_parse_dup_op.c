#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int reg_syntax_t ;
typedef  int /*<<< orphan*/  reg_errcode_t ;
struct TYPE_17__ {char c; } ;
struct TYPE_20__ {scalar_t__ type; TYPE_1__ opr; } ;
typedef  TYPE_4__ re_token_t ;
typedef  int /*<<< orphan*/  re_string_t ;
typedef  int /*<<< orphan*/  re_dfa_t ;
struct TYPE_18__ {scalar_t__ idx; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_2__ opr; } ;
struct TYPE_21__ {TYPE_3__ token; } ;
typedef  TYPE_5__ bin_tree_t ;

/* Variables and functions */
 scalar_t__ BE (int,int) ; 
 scalar_t__ CHARACTER ; 
 int /*<<< orphan*/  CONCAT ; 
 scalar_t__ END_OF_RE ; 
 int /*<<< orphan*/  OP_ALT ; 
 scalar_t__ OP_CLOSE_DUP_NUM ; 
 int /*<<< orphan*/  OP_DUP_ASTERISK ; 
 scalar_t__ OP_DUP_PLUS ; 
 scalar_t__ OP_DUP_QUESTION ; 
 scalar_t__ OP_OPEN_DUP_NUM ; 
 int /*<<< orphan*/  REG_BADBR ; 
 int /*<<< orphan*/  REG_EBRACE ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int RE_INVALID_INTERVAL_ORD ; 
 scalar_t__ SUBEXP ; 
 TYPE_5__* create_tree (int /*<<< orphan*/ *,TYPE_5__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* duplicate_tree (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int fetch_number (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  fetch_token (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_tree ; 
 int /*<<< orphan*/  mark_opt_subexp ; 
 int /*<<< orphan*/  postorder (TYPE_5__*,int /*<<< orphan*/ ,void*) ; 
 int re_string_cur_idx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  re_string_set_index (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bin_tree_t *
parse_dup_op (bin_tree_t *elem, re_string_t *regexp, re_dfa_t *dfa,
	      re_token_t *token, reg_syntax_t syntax, reg_errcode_t *err)
{
  bin_tree_t *tree = NULL, *old_tree = NULL;
  int i, start, end, start_idx = re_string_cur_idx (regexp);
  re_token_t start_token = *token;

  if (token->type == OP_OPEN_DUP_NUM)
    {
      end = 0;
      start = fetch_number (regexp, token, syntax);
      if (start == -1)
	{
	  if (token->type == CHARACTER && token->opr.c == ',')
	    start = 0; /* We treat "{,m}" as "{0,m}".  */
	  else
	    {
	      *err = REG_BADBR; /* <re>{} is invalid.  */
	      return NULL;
	    }
	}
      if (BE (start != -2, 1))
	{
	  /* We treat "{n}" as "{n,n}".  */
	  end = ((token->type == OP_CLOSE_DUP_NUM) ? start
		 : ((token->type == CHARACTER && token->opr.c == ',')
		    ? fetch_number (regexp, token, syntax) : -2));
	}
      if (BE (start == -2 || end == -2, 0))
	{
	  /* Invalid sequence.  */
	  if (BE (!(syntax & RE_INVALID_INTERVAL_ORD), 0))
	    {
	      if (token->type == END_OF_RE)
		*err = REG_EBRACE;
	      else
		*err = REG_BADBR;

	      return NULL;
	    }

	  /* If the syntax bit is set, rollback.  */
	  re_string_set_index (regexp, start_idx);
	  *token = start_token;
	  token->type = CHARACTER;
	  /* mb_partial and word_char bits should be already initialized by
	     peek_token.  */
	  return elem;
	}

      if (BE ((end != -1 && start > end) || token->type != OP_CLOSE_DUP_NUM, 0))
	{
	  /* First number greater than second.  */
	  *err = REG_BADBR;
	  return NULL;
	}
    }
  else
    {
      start = (token->type == OP_DUP_PLUS) ? 1 : 0;
      end = (token->type == OP_DUP_QUESTION) ? 1 : -1;
    }

  fetch_token (token, regexp, syntax);

  if (BE (elem == NULL, 0))
    return NULL;
  if (BE (start == 0 && end == 0, 0))
    {
      postorder (elem, free_tree, NULL);
      return NULL;
    }

  /* Extract "<re>{n,m}" to "<re><re>...<re><re>{0,<m-n>}".  */
  if (BE (start > 0, 0))
    {
      tree = elem;
      for (i = 2; i <= start; ++i)
	{
	  elem = duplicate_tree (elem, dfa);
	  tree = create_tree (dfa, tree, elem, CONCAT);
	  if (BE (elem == NULL || tree == NULL, 0))
	    goto parse_dup_op_espace;
	}

      if (start == end)
	return tree;

      /* Duplicate ELEM before it is marked optional.  */
      elem = duplicate_tree (elem, dfa);
      old_tree = tree;
    }
  else
    old_tree = NULL;

  if (elem->token.type == SUBEXP)
    postorder (elem, mark_opt_subexp, (void *) (long) elem->token.opr.idx);

  tree = create_tree (dfa, elem, NULL, (end == -1 ? OP_DUP_ASTERISK : OP_ALT));
  if (BE (tree == NULL, 0))
    goto parse_dup_op_espace;

  /* This loop is actually executed only when end != -1,
     to rewrite <re>{0,n} as (<re>(<re>...<re>?)?)?...  We have
     already created the start+1-th copy.  */
  for (i = start + 2; i <= end; ++i)
    {
      elem = duplicate_tree (elem, dfa);
      tree = create_tree (dfa, tree, elem, CONCAT);
      if (BE (elem == NULL || tree == NULL, 0))
	goto parse_dup_op_espace;

      tree = create_tree (dfa, tree, NULL, OP_ALT);
      if (BE (tree == NULL, 0))
	goto parse_dup_op_espace;
    }

  if (old_tree)
    tree = create_tree (dfa, old_tree, tree, CONCAT);

  return tree;

 parse_dup_op_espace:
  *err = REG_ESPACE;
  return NULL;
}
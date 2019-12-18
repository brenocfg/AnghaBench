#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ buffer; } ;
typedef  TYPE_1__ regex_t ;
typedef  int reg_syntax_t ;
typedef  scalar_t__ reg_errcode_t ;
struct TYPE_9__ {scalar_t__ type; } ;
typedef  TYPE_2__ re_token_t ;
typedef  int /*<<< orphan*/  re_string_t ;
typedef  int /*<<< orphan*/  re_dfa_t ;
typedef  int /*<<< orphan*/  bin_tree_t ;

/* Variables and functions */
 scalar_t__ BE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ END_OF_RE ; 
 scalar_t__ OP_ALT ; 
 scalar_t__ OP_CLOSE_SUBEXP ; 
 scalar_t__ REG_ESPACE ; 
 scalar_t__ REG_NOERROR ; 
 int RE_CARET_ANCHORS_HERE ; 
 int /*<<< orphan*/ * create_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fetch_token (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * parse_branch (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int,int,scalar_t__*) ; 

__attribute__((used)) static bin_tree_t *
parse_reg_exp (re_string_t *regexp, regex_t *preg, re_token_t *token,
	       reg_syntax_t syntax, int nest, reg_errcode_t *err)
{
  re_dfa_t *dfa = (re_dfa_t *) preg->buffer;
  bin_tree_t *tree, *branch = NULL;
  tree = parse_branch (regexp, preg, token, syntax, nest, err);
  if (BE (*err != REG_NOERROR && tree == NULL, 0))
    return NULL;

  while (token->type == OP_ALT)
    {
      fetch_token (token, regexp, syntax | RE_CARET_ANCHORS_HERE);
      if (token->type != OP_ALT && token->type != END_OF_RE
	  && (nest == 0 || token->type != OP_CLOSE_SUBEXP))
	{
	  branch = parse_branch (regexp, preg, token, syntax, nest, err);
	  if (BE (*err != REG_NOERROR && branch == NULL, 0))
	    return NULL;
	}
      else
	branch = NULL;
      tree = create_tree (dfa, tree, branch, OP_ALT);
      if (BE (tree == NULL, 0))
	{
	  *err = REG_ESPACE;
	  return NULL;
	}
    }
  return tree;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ buffer; } ;
typedef  TYPE_1__ regex_t ;
typedef  int /*<<< orphan*/  reg_syntax_t ;
typedef  scalar_t__ reg_errcode_t ;
struct TYPE_8__ {scalar_t__ type; } ;
typedef  TYPE_2__ re_token_t ;
typedef  int /*<<< orphan*/  re_string_t ;
typedef  int /*<<< orphan*/  re_dfa_t ;
typedef  int /*<<< orphan*/  bin_tree_t ;

/* Variables and functions */
 scalar_t__ BE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONCAT ; 
 scalar_t__ END_OF_RE ; 
 scalar_t__ OP_ALT ; 
 scalar_t__ OP_CLOSE_SUBEXP ; 
 scalar_t__ REG_ESPACE ; 
 scalar_t__ REG_NOERROR ; 
 int /*<<< orphan*/ * create_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * parse_expression (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int,scalar_t__*) ; 

__attribute__((used)) static bin_tree_t *
parse_branch (re_string_t *regexp, regex_t *preg, re_token_t *token,
	      reg_syntax_t syntax, int nest, reg_errcode_t *err)
{
  bin_tree_t *tree, *exp;
  re_dfa_t *dfa = (re_dfa_t *) preg->buffer;
  tree = parse_expression (regexp, preg, token, syntax, nest, err);
  if (BE (*err != REG_NOERROR && tree == NULL, 0))
    return NULL;

  while (token->type != OP_ALT && token->type != END_OF_RE
	 && (nest == 0 || token->type != OP_CLOSE_SUBEXP))
    {
      exp = parse_expression (regexp, preg, token, syntax, nest, err);
      if (BE (*err != REG_NOERROR && exp == NULL, 0))
	{
	  return NULL;
	}
      if (tree != NULL && exp != NULL)
	{
	  tree = create_tree (dfa, tree, exp, CONCAT);
	  if (tree == NULL)
	    {
	      *err = REG_ESPACE;
	      return NULL;
	    }
	}
      else if (tree == NULL)
	tree = exp;
      /* Otherwise exp == NULL, we don't need to create new tree.  */
    }
  return tree;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ buffer; } ;
typedef  TYPE_1__ regex_t ;
typedef  int reg_syntax_t ;
typedef  scalar_t__ reg_errcode_t ;
typedef  int /*<<< orphan*/  re_token_t ;
typedef  int /*<<< orphan*/  re_string_t ;
struct TYPE_7__ {int syntax; } ;
typedef  TYPE_2__ re_dfa_t ;
typedef  int /*<<< orphan*/  bin_tree_t ;

/* Variables and functions */
 scalar_t__ BE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONCAT ; 
 int /*<<< orphan*/  END_OF_RE ; 
 scalar_t__ REG_ESPACE ; 
 scalar_t__ REG_NOERROR ; 
 int RE_CARET_ANCHORS_HERE ; 
 int /*<<< orphan*/ * create_tree (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_token (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * parse_reg_exp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static bin_tree_t *
parse (re_string_t *regexp, regex_t *preg, reg_syntax_t syntax,
       reg_errcode_t *err)
{
  re_dfa_t *dfa = (re_dfa_t *) preg->buffer;
  bin_tree_t *tree, *eor, *root;
  re_token_t current_token;
  dfa->syntax = syntax;
  fetch_token (&current_token, regexp, syntax | RE_CARET_ANCHORS_HERE);
  tree = parse_reg_exp (regexp, preg, &current_token, syntax, 0, err);
  if (BE (*err != REG_NOERROR && tree == NULL, 0))
    return NULL;
  eor = create_tree (dfa, NULL, NULL, END_OF_RE);
  if (tree != NULL)
    root = create_tree (dfa, tree, eor, CONCAT);
  else
    root = eor;
  if (BE (eor == NULL || root == NULL, 0))
    {
      *err = REG_ESPACE;
      return NULL;
    }
  return root;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ reg_errcode_t ;
struct TYPE_4__ {int /*<<< orphan*/ * sbcset; } ;
struct TYPE_5__ {TYPE_1__ opr; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ re_token_t ;
typedef  int /*<<< orphan*/  re_dfa_t ;
typedef  int /*<<< orphan*/ * re_bitset_ptr_t ;
typedef  int /*<<< orphan*/  bitset_t ;
typedef  int /*<<< orphan*/  bin_tree_t ;
typedef  int /*<<< orphan*/  RE_TRANSLATE_TYPE ;

/* Variables and functions */
 scalar_t__ BE (int,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_ESPACE ; 
 scalar_t__ REG_NOERROR ; 
 int /*<<< orphan*/  SIMPLE_BRACKET ; 
 int /*<<< orphan*/  bitset_not (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitset_set (int /*<<< orphan*/ *,char const) ; 
 scalar_t__ build_charclass (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/ * create_token_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  re_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bin_tree_t *
build_charclass_op (re_dfa_t *dfa, RE_TRANSLATE_TYPE trans,
		    const char *class_name,
		    const char *extra, int non_match,
		    reg_errcode_t *err)
{
  re_bitset_ptr_t sbcset;
#ifdef RE_ENABLE_I18N
  re_charset_t *mbcset;
  int alloc = 0;
#endif /* not RE_ENABLE_I18N */
  reg_errcode_t ret;
  re_token_t br_token;
  bin_tree_t *tree;

  sbcset = (re_bitset_ptr_t) calloc (sizeof (bitset_t), 1);
#ifdef RE_ENABLE_I18N
  mbcset = (re_charset_t *) calloc (sizeof (re_charset_t), 1);
#endif /* RE_ENABLE_I18N */

#ifdef RE_ENABLE_I18N
  if (BE (sbcset == NULL || mbcset == NULL, 0))
#else /* not RE_ENABLE_I18N */
  if (BE (sbcset == NULL, 0))
#endif /* not RE_ENABLE_I18N */
    {
      *err = REG_ESPACE;
      return NULL;
    }

  if (non_match)
    {
#ifdef RE_ENABLE_I18N
      mbcset->non_match = 1;
#endif /* not RE_ENABLE_I18N */
    }

  /* We don't care the syntax in this case.  */
  ret = build_charclass (trans, sbcset,
#ifdef RE_ENABLE_I18N
			 mbcset, &alloc,
#endif /* RE_ENABLE_I18N */
			 class_name, 0);

  if (BE (ret != REG_NOERROR, 0))
    {
      re_free (sbcset);
#ifdef RE_ENABLE_I18N
      free_charset (mbcset);
#endif /* RE_ENABLE_I18N */
      *err = ret;
      return NULL;
    }
  /* \w match '_' also.  */
  for (; *extra; extra++)
    bitset_set (sbcset, *extra);

  /* If it is non-matching list.  */
  if (non_match)
    bitset_not (sbcset);

#ifdef RE_ENABLE_I18N
  /* Ensure only single byte characters are set.  */
  if (dfa->mb_cur_max > 1)
    bitset_mask (sbcset, dfa->sb_char);
#endif

  /* Build a tree for simple bracket.  */
  br_token.type = SIMPLE_BRACKET;
  br_token.opr.sbcset = sbcset;
  tree = create_token_tree (dfa, NULL, NULL, &br_token);
  if (BE (tree == NULL, 0))
    goto build_word_op_espace;

#ifdef RE_ENABLE_I18N
  if (dfa->mb_cur_max > 1)
    {
      bin_tree_t *mbc_tree;
      /* Build a tree for complex bracket.  */
      br_token.type = COMPLEX_BRACKET;
      br_token.opr.mbcset = mbcset;
      dfa->has_mb_node = 1;
      mbc_tree = create_token_tree (dfa, NULL, NULL, &br_token);
      if (BE (mbc_tree == NULL, 0))
	goto build_word_op_espace;
      /* Then join them by ALT node.  */
      tree = create_tree (dfa, tree, mbc_tree, OP_ALT);
      if (BE (mbc_tree != NULL, 1))
	return tree;
    }
  else
    {
      free_charset (mbcset);
      return tree;
    }
#else /* not RE_ENABLE_I18N */
  return tree;
#endif /* not RE_ENABLE_I18N */

 build_word_op_espace:
  re_free (sbcset);
#ifdef RE_ENABLE_I18N
  free_charset (mbcset);
#endif /* RE_ENABLE_I18N */
  *err = REG_ESPACE;
  return NULL;
}
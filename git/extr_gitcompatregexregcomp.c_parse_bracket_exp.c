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
typedef  scalar_t__ reg_errcode_t ;
struct TYPE_18__ {int /*<<< orphan*/ * sbcset; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_2__ opr; } ;
typedef  TYPE_3__ re_token_t ;
struct TYPE_20__ {int /*<<< orphan*/  trans; } ;
typedef  TYPE_4__ re_string_t ;
typedef  int /*<<< orphan*/  re_dfa_t ;
typedef  int /*<<< orphan*/ * re_bitset_ptr_t ;
struct TYPE_17__ {unsigned char* name; char ch; } ;
struct TYPE_21__ {int type; TYPE_1__ opr; } ;
typedef  TYPE_5__ bracket_elem_t ;
typedef  int /*<<< orphan*/  bitset_t ;
typedef  int /*<<< orphan*/  bin_tree_t ;

/* Variables and functions */
 scalar_t__ BE (int,int /*<<< orphan*/ ) ; 
 int BRACKET_NAME_BUF_SIZE ; 
 void* CHARACTER ; 
#define  CHAR_CLASS 131 
#define  COLL_SYM 130 
 scalar_t__ END_OF_RE ; 
#define  EQUIV_CLASS 129 
 scalar_t__ OP_CHARSET_RANGE ; 
 scalar_t__ OP_CLOSE_BRACKET ; 
 scalar_t__ OP_NON_MATCH_LIST ; 
 scalar_t__ REG_BADPAT ; 
 scalar_t__ REG_EBRACK ; 
 scalar_t__ REG_ESPACE ; 
 scalar_t__ REG_NOERROR ; 
 int RE_HAT_LISTS_NOT_NEWLINE ; 
#define  SB_CHAR 128 
 scalar_t__ SIMPLE_BRACKET ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitset_not (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitset_set (int /*<<< orphan*/ *,char) ; 
 scalar_t__ build_charclass (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ build_collating_symbol (int /*<<< orphan*/ *,unsigned char*) ; 
 scalar_t__ build_equiv_class (int /*<<< orphan*/ *,unsigned char*) ; 
 scalar_t__ build_range_exp (int /*<<< orphan*/ *,TYPE_5__*,TYPE_5__*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/ * create_token_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ parse_bracket_element (TYPE_5__*,TYPE_4__*,TYPE_3__*,int,int /*<<< orphan*/ *,int,int) ; 
 int peek_token_bracket (TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  re_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  re_string_skip_bytes (TYPE_4__*,int) ; 

__attribute__((used)) static bin_tree_t *
parse_bracket_exp (re_string_t *regexp, re_dfa_t *dfa, re_token_t *token,
		   reg_syntax_t syntax, reg_errcode_t *err)
{
#ifdef _LIBC
  const unsigned char *collseqmb;
  const char *collseqwc;
  uint32_t nrules;
  int32_t table_size;
  const int32_t *symb_table;
  const unsigned char *extra;

  /* Local function for parse_bracket_exp used in _LIBC environment.
     Seek the collating symbol entry correspondings to NAME.
     Return the index of the symbol in the SYMB_TABLE.  */

  auto inline int32_t
  __attribute ((always_inline))
  seek_collating_symbol_entry (name, name_len)
	 const unsigned char *name;
	 size_t name_len;
    {
      int32_t hash = elem_hash ((const char *) name, name_len);
      int32_t elem = hash % table_size;
      if (symb_table[2 * elem] != 0)
	{
	  int32_t second = hash % (table_size - 2) + 1;

	  do
	    {
	      /* First compare the hashing value.  */
	      if (symb_table[2 * elem] == hash
		  /* Compare the length of the name.  */
		  && name_len == extra[symb_table[2 * elem + 1]]
		  /* Compare the name.  */
		  && memcmp (name, &extra[symb_table[2 * elem + 1] + 1],
			     name_len) == 0)
		{
		  /* Yep, this is the entry.  */
		  break;
		}

	      /* Next entry.  */
	      elem += second;
	    }
	  while (symb_table[2 * elem] != 0);
	}
      return elem;
    }

  /* Local function for parse_bracket_exp used in _LIBC environment.
     Look up the collation sequence value of BR_ELEM.
     Return the value if succeeded, UINT_MAX otherwise.  */

  auto inline unsigned int
  __attribute ((always_inline))
  lookup_collation_sequence_value (br_elem)
	 bracket_elem_t *br_elem;
    {
      if (br_elem->type == SB_CHAR)
	{
	  /*
	  if (MB_CUR_MAX == 1)
	  */
	  if (nrules == 0)
	    return collseqmb[br_elem->opr.ch];
	  else
	    {
	      wint_t wc = __btowc (br_elem->opr.ch);
	      return __collseq_table_lookup (collseqwc, wc);
	    }
	}
      else if (br_elem->type == MB_CHAR)
	{
	  if (nrules != 0)
	    return __collseq_table_lookup (collseqwc, br_elem->opr.wch);
	}
      else if (br_elem->type == COLL_SYM)
	{
	  size_t sym_name_len = strlen ((char *) br_elem->opr.name);
	  if (nrules != 0)
	    {
	      int32_t elem, idx;
	      elem = seek_collating_symbol_entry (br_elem->opr.name,
						  sym_name_len);
	      if (symb_table[2 * elem] != 0)
		{
		  /* We found the entry.  */
		  idx = symb_table[2 * elem + 1];
		  /* Skip the name of collating element name.  */
		  idx += 1 + extra[idx];
		  /* Skip the byte sequence of the collating element.  */
		  idx += 1 + extra[idx];
		  /* Adjust for the alignment.  */
		  idx = (idx + 3) & ~3;
		  /* Skip the multibyte collation sequence value.  */
		  idx += sizeof (unsigned int);
		  /* Skip the wide char sequence of the collating element.  */
		  idx += sizeof (unsigned int) *
		    (1 + *(unsigned int *) (extra + idx));
		  /* Return the collation sequence value.  */
		  return *(unsigned int *) (extra + idx);
		}
	      else if (symb_table[2 * elem] == 0 && sym_name_len == 1)
		{
		  /* No valid character.  Match it as a single byte
		     character.  */
		  return collseqmb[br_elem->opr.name[0]];
		}
	    }
	  else if (sym_name_len == 1)
	    return collseqmb[br_elem->opr.name[0]];
	}
      return UINT_MAX;
    }

  /* Local function for parse_bracket_exp used in _LIBC environment.
     Build the range expression which starts from START_ELEM, and ends
     at END_ELEM.  The result are written to MBCSET and SBCSET.
     RANGE_ALLOC is the allocated size of mbcset->range_starts, and
     mbcset->range_ends, is a pointer argument since we may
     update it.  */

  auto inline reg_errcode_t
  __attribute ((always_inline))
  build_range_exp (sbcset, mbcset, range_alloc, start_elem, end_elem)
	 re_charset_t *mbcset;
	 int *range_alloc;
	 bitset_t sbcset;
	 bracket_elem_t *start_elem, *end_elem;
    {
      unsigned int ch;
      uint32_t start_collseq;
      uint32_t end_collseq;

      /* Equivalence Classes and Character Classes can't be a range
	 start/end.  */
      if (BE (start_elem->type == EQUIV_CLASS || start_elem->type == CHAR_CLASS
	      || end_elem->type == EQUIV_CLASS || end_elem->type == CHAR_CLASS,
	      0))
	return REG_ERANGE;

      start_collseq = lookup_collation_sequence_value (start_elem);
      end_collseq = lookup_collation_sequence_value (end_elem);
      /* Check start/end collation sequence values.  */
      if (BE (start_collseq == UINT_MAX || end_collseq == UINT_MAX, 0))
	return REG_ECOLLATE;
      if (BE ((syntax & RE_NO_EMPTY_RANGES) && start_collseq > end_collseq, 0))
	return REG_ERANGE;

      /* Got valid collation sequence values, add them as a new entry.
	 However, if we have no collation elements, and the character set
	 is single byte, the single byte character set that we
	 build below suffices. */
      if (nrules > 0 || dfa->mb_cur_max > 1)
	{
	  /* Check the space of the arrays.  */
	  if (BE (*range_alloc == mbcset->nranges, 0))
	    {
	      /* There is not enough space, need realloc.  */
	      uint32_t *new_array_start;
	      uint32_t *new_array_end;
	      int new_nranges;

	      /* +1 in case of mbcset->nranges is 0.  */
	      new_nranges = 2 * mbcset->nranges + 1;
	      new_array_start = re_realloc (mbcset->range_starts, uint32_t,
					    new_nranges);
	      new_array_end = re_realloc (mbcset->range_ends, uint32_t,
					  new_nranges);

	      if (BE (new_array_start == NULL || new_array_end == NULL, 0))
		return REG_ESPACE;

	      mbcset->range_starts = new_array_start;
	      mbcset->range_ends = new_array_end;
	      *range_alloc = new_nranges;
	    }

	  mbcset->range_starts[mbcset->nranges] = start_collseq;
	  mbcset->range_ends[mbcset->nranges++] = end_collseq;
	}

      /* Build the table for single byte characters.  */
      for (ch = 0; ch < SBC_MAX; ch++)
	{
	  uint32_t ch_collseq;
	  /*
	  if (MB_CUR_MAX == 1)
	  */
	  if (nrules == 0)
	    ch_collseq = collseqmb[ch];
	  else
	    ch_collseq = __collseq_table_lookup (collseqwc, __btowc (ch));
	  if (start_collseq <= ch_collseq && ch_collseq <= end_collseq)
	    bitset_set (sbcset, ch);
	}
      return REG_NOERROR;
    }

  /* Local function for parse_bracket_exp used in _LIBC environment.
     Build the collating element which is represented by NAME.
     The result are written to MBCSET and SBCSET.
     COLL_SYM_ALLOC is the allocated size of mbcset->coll_sym, is a
     pointer argument since we may update it.  */

  auto inline reg_errcode_t
  __attribute ((always_inline))
  build_collating_symbol (sbcset, mbcset, coll_sym_alloc, name)
	 re_charset_t *mbcset;
	 int *coll_sym_alloc;
	 bitset_t sbcset;
	 const unsigned char *name;
    {
      int32_t elem, idx;
      size_t name_len = strlen ((const char *) name);
      if (nrules != 0)
	{
	  elem = seek_collating_symbol_entry (name, name_len);
	  if (symb_table[2 * elem] != 0)
	    {
	      /* We found the entry.  */
	      idx = symb_table[2 * elem + 1];
	      /* Skip the name of collating element name.  */
	      idx += 1 + extra[idx];
	    }
	  else if (symb_table[2 * elem] == 0 && name_len == 1)
	    {
	      /* No valid character, treat it as a normal
		 character.  */
	      bitset_set (sbcset, name[0]);
	      return REG_NOERROR;
	    }
	  else
	    return REG_ECOLLATE;

	  /* Got valid collation sequence, add it as a new entry.  */
	  /* Check the space of the arrays.  */
	  if (BE (*coll_sym_alloc == mbcset->ncoll_syms, 0))
	    {
	      /* Not enough, realloc it.  */
	      /* +1 in case of mbcset->ncoll_syms is 0.  */
	      int new_coll_sym_alloc = 2 * mbcset->ncoll_syms + 1;
	      /* Use realloc since mbcset->coll_syms is NULL
		 if *alloc == 0.  */
	      int32_t *new_coll_syms = re_realloc (mbcset->coll_syms, int32_t,
						   new_coll_sym_alloc);
	      if (BE (new_coll_syms == NULL, 0))
		return REG_ESPACE;
	      mbcset->coll_syms = new_coll_syms;
	      *coll_sym_alloc = new_coll_sym_alloc;
	    }
	  mbcset->coll_syms[mbcset->ncoll_syms++] = idx;
	  return REG_NOERROR;
	}
      else
	{
	  if (BE (name_len != 1, 0))
	    return REG_ECOLLATE;
	  else
	    {
	      bitset_set (sbcset, name[0]);
	      return REG_NOERROR;
	    }
	}
    }
#endif

  re_token_t br_token;
  re_bitset_ptr_t sbcset;
#ifdef RE_ENABLE_I18N
  re_charset_t *mbcset;
  int coll_sym_alloc = 0, range_alloc = 0, mbchar_alloc = 0;
  int equiv_class_alloc = 0, char_class_alloc = 0;
#endif /* not RE_ENABLE_I18N */
  int non_match = 0;
  bin_tree_t *work_tree;
  int token_len;
  int first_round = 1;
#ifdef _LIBC
  collseqmb = (const unsigned char *)
    _NL_CURRENT (LC_COLLATE, _NL_COLLATE_COLLSEQMB);
  nrules = _NL_CURRENT_WORD (LC_COLLATE, _NL_COLLATE_NRULES);
  if (nrules)
    {
      /*
      if (MB_CUR_MAX > 1)
      */
      collseqwc = _NL_CURRENT (LC_COLLATE, _NL_COLLATE_COLLSEQWC);
      table_size = _NL_CURRENT_WORD (LC_COLLATE, _NL_COLLATE_SYMB_HASH_SIZEMB);
      symb_table = (const int32_t *) _NL_CURRENT (LC_COLLATE,
						  _NL_COLLATE_SYMB_TABLEMB);
      extra = (const unsigned char *) _NL_CURRENT (LC_COLLATE,
						   _NL_COLLATE_SYMB_EXTRAMB);
    }
#endif
  sbcset = (re_bitset_ptr_t) calloc (sizeof (bitset_t), 1);
#ifdef RE_ENABLE_I18N
  mbcset = (re_charset_t *) calloc (sizeof (re_charset_t), 1);
#endif /* RE_ENABLE_I18N */
#ifdef RE_ENABLE_I18N
  if (BE (sbcset == NULL || mbcset == NULL, 0))
#else
  if (BE (sbcset == NULL, 0))
#endif /* RE_ENABLE_I18N */
    {
      *err = REG_ESPACE;
      return NULL;
    }

  token_len = peek_token_bracket (token, regexp, syntax);
  if (BE (token->type == END_OF_RE, 0))
    {
      *err = REG_BADPAT;
      goto parse_bracket_exp_free_return;
    }
  if (token->type == OP_NON_MATCH_LIST)
    {
#ifdef RE_ENABLE_I18N
      mbcset->non_match = 1;
#endif /* not RE_ENABLE_I18N */
      non_match = 1;
      if (syntax & RE_HAT_LISTS_NOT_NEWLINE)
	bitset_set (sbcset, '\n');
      re_string_skip_bytes (regexp, token_len); /* Skip a token.  */
      token_len = peek_token_bracket (token, regexp, syntax);
      if (BE (token->type == END_OF_RE, 0))
	{
	  *err = REG_BADPAT;
	  goto parse_bracket_exp_free_return;
	}
    }

  /* We treat the first ']' as a normal character.  */
  if (token->type == OP_CLOSE_BRACKET)
    token->type = CHARACTER;

  while (1)
    {
      bracket_elem_t start_elem, end_elem;
      unsigned char start_name_buf[BRACKET_NAME_BUF_SIZE];
      unsigned char end_name_buf[BRACKET_NAME_BUF_SIZE];
      reg_errcode_t ret;
      int token_len2 = 0, is_range_exp = 0;
      re_token_t token2;

      start_elem.opr.name = start_name_buf;
      ret = parse_bracket_element (&start_elem, regexp, token, token_len, dfa,
				   syntax, first_round);
      if (BE (ret != REG_NOERROR, 0))
	{
	  *err = ret;
	  goto parse_bracket_exp_free_return;
	}
      first_round = 0;

      /* Get information about the next token.  We need it in any case.  */
      token_len = peek_token_bracket (token, regexp, syntax);

      /* Do not check for ranges if we know they are not allowed.  */
      if (start_elem.type != CHAR_CLASS && start_elem.type != EQUIV_CLASS)
	{
	  if (BE (token->type == END_OF_RE, 0))
	    {
	      *err = REG_EBRACK;
	      goto parse_bracket_exp_free_return;
	    }
	  if (token->type == OP_CHARSET_RANGE)
	    {
	      re_string_skip_bytes (regexp, token_len); /* Skip '-'.  */
	      token_len2 = peek_token_bracket (&token2, regexp, syntax);
	      if (BE (token2.type == END_OF_RE, 0))
		{
		  *err = REG_EBRACK;
		  goto parse_bracket_exp_free_return;
		}
	      if (token2.type == OP_CLOSE_BRACKET)
		{
		  /* We treat the last '-' as a normal character.  */
		  re_string_skip_bytes (regexp, -token_len);
		  token->type = CHARACTER;
		}
	      else
		is_range_exp = 1;
	    }
	}

      if (is_range_exp == 1)
	{
	  end_elem.opr.name = end_name_buf;
	  ret = parse_bracket_element (&end_elem, regexp, &token2, token_len2,
				       dfa, syntax, 1);
	  if (BE (ret != REG_NOERROR, 0))
	    {
	      *err = ret;
	      goto parse_bracket_exp_free_return;
	    }

	  token_len = peek_token_bracket (token, regexp, syntax);

#ifdef _LIBC
	  *err = build_range_exp (sbcset, mbcset, &range_alloc,
				  &start_elem, &end_elem);
#else
# ifdef RE_ENABLE_I18N
	  *err = build_range_exp (sbcset,
				  dfa->mb_cur_max > 1 ? mbcset : NULL,
				  &range_alloc, &start_elem, &end_elem);
# else
	  *err = build_range_exp (sbcset, &start_elem, &end_elem);
# endif
#endif /* RE_ENABLE_I18N */
	  if (BE (*err != REG_NOERROR, 0))
	    goto parse_bracket_exp_free_return;
	}
      else
	{
	  switch (start_elem.type)
	    {
	    case SB_CHAR:
	      bitset_set (sbcset, start_elem.opr.ch);
	      break;
#ifdef RE_ENABLE_I18N
	    case MB_CHAR:
	      /* Check whether the array has enough space.  */
	      if (BE (mbchar_alloc == mbcset->nmbchars, 0))
		{
		  wchar_t *new_mbchars;
		  /* Not enough, realloc it.  */
		  /* +1 in case of mbcset->nmbchars is 0.  */
		  mbchar_alloc = 2 * mbcset->nmbchars + 1;
		  /* Use realloc since array is NULL if *alloc == 0.  */
		  new_mbchars = re_realloc (mbcset->mbchars, wchar_t,
					    mbchar_alloc);
		  if (BE (new_mbchars == NULL, 0))
		    goto parse_bracket_exp_espace;
		  mbcset->mbchars = new_mbchars;
		}
	      mbcset->mbchars[mbcset->nmbchars++] = start_elem.opr.wch;
	      break;
#endif /* RE_ENABLE_I18N */
	    case EQUIV_CLASS:
	      *err = build_equiv_class (sbcset,
#ifdef RE_ENABLE_I18N
					mbcset, &equiv_class_alloc,
#endif /* RE_ENABLE_I18N */
					start_elem.opr.name);
	      if (BE (*err != REG_NOERROR, 0))
		goto parse_bracket_exp_free_return;
	      break;
	    case COLL_SYM:
	      *err = build_collating_symbol (sbcset,
#ifdef RE_ENABLE_I18N
					     mbcset, &coll_sym_alloc,
#endif /* RE_ENABLE_I18N */
					     start_elem.opr.name);
	      if (BE (*err != REG_NOERROR, 0))
		goto parse_bracket_exp_free_return;
	      break;
	    case CHAR_CLASS:
	      *err = build_charclass (regexp->trans, sbcset,
#ifdef RE_ENABLE_I18N
				      mbcset, &char_class_alloc,
#endif /* RE_ENABLE_I18N */
				      (const char *) start_elem.opr.name, syntax);
	      if (BE (*err != REG_NOERROR, 0))
	       goto parse_bracket_exp_free_return;
	      break;
	    default:
	      assert (0);
	      break;
	    }
	}
      if (BE (token->type == END_OF_RE, 0))
	{
	  *err = REG_EBRACK;
	  goto parse_bracket_exp_free_return;
	}
      if (token->type == OP_CLOSE_BRACKET)
	break;
    }

  re_string_skip_bytes (regexp, token_len); /* Skip a token.  */

  /* If it is non-matching list.  */
  if (non_match)
    bitset_not (sbcset);

#ifdef RE_ENABLE_I18N
  /* Ensure only single byte characters are set.  */
  if (dfa->mb_cur_max > 1)
    bitset_mask (sbcset, dfa->sb_char);

  if (mbcset->nmbchars || mbcset->ncoll_syms || mbcset->nequiv_classes
      || mbcset->nranges || (dfa->mb_cur_max > 1 && (mbcset->nchar_classes
						     || mbcset->non_match)))
    {
      bin_tree_t *mbc_tree;
      int sbc_idx;
      /* Build a tree for complex bracket.  */
      dfa->has_mb_node = 1;
      br_token.type = COMPLEX_BRACKET;
      br_token.opr.mbcset = mbcset;
      mbc_tree = create_token_tree (dfa, NULL, NULL, &br_token);
      if (BE (mbc_tree == NULL, 0))
	goto parse_bracket_exp_espace;
      for (sbc_idx = 0; sbc_idx < BITSET_WORDS; ++sbc_idx)
	if (sbcset[sbc_idx])
	  break;
      /* If there are no bits set in sbcset, there is no point
	 of having both SIMPLE_BRACKET and COMPLEX_BRACKET.  */
      if (sbc_idx < BITSET_WORDS)
	{
	  /* Build a tree for simple bracket.  */
	  br_token.type = SIMPLE_BRACKET;
	  br_token.opr.sbcset = sbcset;
	  work_tree = create_token_tree (dfa, NULL, NULL, &br_token);
	  if (BE (work_tree == NULL, 0))
	    goto parse_bracket_exp_espace;

	  /* Then join them by ALT node.  */
	  work_tree = create_tree (dfa, work_tree, mbc_tree, OP_ALT);
	  if (BE (work_tree == NULL, 0))
	    goto parse_bracket_exp_espace;
	}
      else
	{
	  re_free (sbcset);
	  work_tree = mbc_tree;
	}
    }
  else
#endif /* not RE_ENABLE_I18N */
    {
#ifdef RE_ENABLE_I18N
      free_charset (mbcset);
#endif
      /* Build a tree for simple bracket.  */
      br_token.type = SIMPLE_BRACKET;
      br_token.opr.sbcset = sbcset;
      work_tree = create_token_tree (dfa, NULL, NULL, &br_token);
      if (BE (work_tree == NULL, 0))
	goto parse_bracket_exp_espace;
    }
  return work_tree;

 parse_bracket_exp_espace:
  *err = REG_ESPACE;
 parse_bracket_exp_free_return:
  re_free (sbcset);
#ifdef RE_ENABLE_I18N
  free_charset (mbcset);
#endif /* RE_ENABLE_I18N */
  return NULL;
}
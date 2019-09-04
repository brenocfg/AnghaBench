#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct re_state_table_entry {int dummy; } ;
typedef  int /*<<< orphan*/  reg_errcode_t ;
struct TYPE_4__ {size_t nodes_alloc; unsigned int state_hash_mask; int is_utf8; int /*<<< orphan*/ * state_table; int /*<<< orphan*/ * nodes; scalar_t__ map_notascii; int /*<<< orphan*/  mb_cur_max; int /*<<< orphan*/  str_tree_storage_idx; } ;
typedef  TYPE_1__ re_dfa_t ;

/* Variables and functions */
 scalar_t__ BE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIN_TREE_STORAGE_SIZE ; 
 int /*<<< orphan*/  MB_CUR_MAX ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  REG_NOERROR ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/ * calloc (int,unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,char,int) ; 
 int /*<<< orphan*/ * re_malloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  re_token_t ; 

__attribute__((used)) static reg_errcode_t
init_dfa (re_dfa_t *dfa, size_t pat_len)
{
  unsigned int table_size;

  memset (dfa, '\0', sizeof (re_dfa_t));

  /* Force allocation of str_tree_storage the first time.  */
  dfa->str_tree_storage_idx = BIN_TREE_STORAGE_SIZE;

  /* Avoid overflows.  */
  if (pat_len == SIZE_MAX)
    return REG_ESPACE;

  dfa->nodes_alloc = pat_len + 1;
  dfa->nodes = re_malloc (re_token_t, dfa->nodes_alloc);

  /*  table_size = 2 ^ ceil(log pat_len) */
  for (table_size = 1; ; table_size <<= 1)
    if (table_size > pat_len)
      break;

  dfa->state_table = calloc (sizeof (struct re_state_table_entry), table_size);
  dfa->state_hash_mask = table_size - 1;

  dfa->mb_cur_max = MB_CUR_MAX;
#ifdef _LIBC
  if (dfa->mb_cur_max == 6
      && strcmp (_NL_CURRENT (LC_CTYPE, _NL_CTYPE_CODESET_NAME), "UTF-8") == 0)
    dfa->is_utf8 = 1;
  dfa->map_notascii = (_NL_CURRENT_WORD (LC_CTYPE, _NL_CTYPE_MAP_TO_NONASCII)
		       != 0);
#else
  dfa->is_utf8 = 1;
  /* We check exhaustively in the loop below if this charset is a
     superset of ASCII.  */
  dfa->map_notascii = 0;
#endif

#ifdef RE_ENABLE_I18N
  if (dfa->mb_cur_max > 1)
    {
      if (dfa->is_utf8)
        {
#if !defined(__GNUC__) || __GNUC__ < 3
	  static short utf8_sb_map_inited = 0;

	  if (! utf8_sb_map_inited)
	    {
		int i;

	  	utf8_sb_map_inited = 0;
		for (i = 0; i <= 0x80 / BITSET_WORD_BITS - 1; i++)
		  utf8_sb_map[i] = BITSET_WORD_MAX;
	    }
#endif
	  dfa->sb_char = (re_bitset_ptr_t) utf8_sb_map;
	}
      else
	{
	  int i, j, ch;

	  dfa->sb_char = (re_bitset_ptr_t) calloc (sizeof (bitset_t), 1);
	  if (BE (dfa->sb_char == NULL, 0))
	    return REG_ESPACE;

	  /* Set the bits corresponding to single byte chars.  */
	  for (i = 0, ch = 0; i < BITSET_WORDS; ++i)
	    for (j = 0; j < BITSET_WORD_BITS; ++j, ++ch)
	      {
		wint_t wch = __btowc (ch);
		if (wch != WEOF)
		  dfa->sb_char[i] |= (bitset_word_t) 1 << j;
# ifndef _LIBC
		if (isascii (ch) && wch != ch)
		  dfa->map_notascii = 1;
# endif
	      }
	}
    }
#endif

  if (BE (dfa->nodes == NULL || dfa->state_table == NULL, 0))
    return REG_ESPACE;
  return REG_NOERROR;
}
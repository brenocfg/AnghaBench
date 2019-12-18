#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  state ;
struct TYPE_13__ {int syntax; int can_be_null; scalar_t__ buffer; } ;
typedef  TYPE_4__ regex_t ;
typedef  scalar_t__ re_token_type_t ;
struct TYPE_10__ {int nelem; int* elems; } ;
struct TYPE_14__ {TYPE_1__ nodes; } ;
typedef  TYPE_5__ re_dfastate_t ;
struct TYPE_15__ {int mb_cur_max; int nodes_len; TYPE_3__* nodes; } ;
typedef  TYPE_6__ re_dfa_t ;
struct TYPE_16__ {int nmbchars; int /*<<< orphan*/ * mbchars; scalar_t__ nequiv_classes; scalar_t__ nranges; scalar_t__ non_match; scalar_t__ nchar_classes; scalar_t__ ncoll_syms; } ;
typedef  TYPE_7__ re_charset_t ;
typedef  char mbstate_t ;
typedef  int /*<<< orphan*/  mbs ;
typedef  scalar_t__ int32_t ;
typedef  int bitset_word_t ;
struct TYPE_11__ {unsigned char c; int* sbcset; TYPE_7__* mbcset; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_2__ opr; scalar_t__ mb_partial; } ;

/* Variables and functions */
 int BITSET_WORDS ; 
 int BITSET_WORD_BITS ; 
 scalar_t__ CHARACTER ; 
 scalar_t__ COMPLEX_BRACKET ; 
 scalar_t__ END_OF_RE ; 
 int /*<<< orphan*/  LC_COLLATE ; 
 scalar_t__ OP_PERIOD ; 
 scalar_t__ OP_UTF8_PERIOD ; 
 int RE_ICASE ; 
 int SBC_MAX ; 
 scalar_t__ SIMPLE_BRACKET ; 
 int /*<<< orphan*/  _NL_COLLATE_NRULES ; 
 int /*<<< orphan*/  _NL_COLLATE_TABLEMB ; 
 scalar_t__ _NL_CURRENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _NL_CURRENT_WORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t __mbrtowc (int /*<<< orphan*/ *,char const*,int,char*) ; 
 size_t __wcrtomb (char*,int /*<<< orphan*/ ,char*) ; 
 unsigned char* alloca (int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  re_set_fastmap (char*,int,unsigned char) ; 
 int /*<<< orphan*/  towlower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
re_compile_fastmap_iter (regex_t *bufp, const re_dfastate_t *init_state,
			 char *fastmap)
{
  re_dfa_t *dfa = (re_dfa_t *) bufp->buffer;
  int node_cnt;
  int icase = (dfa->mb_cur_max == 1 && (bufp->syntax & RE_ICASE));
  for (node_cnt = 0; node_cnt < init_state->nodes.nelem; ++node_cnt)
    {
      int node = init_state->nodes.elems[node_cnt];
      re_token_type_t type = dfa->nodes[node].type;

      if (type == CHARACTER)
	{
	  re_set_fastmap (fastmap, icase, dfa->nodes[node].opr.c);
#ifdef RE_ENABLE_I18N
	  if ((bufp->syntax & RE_ICASE) && dfa->mb_cur_max > 1)
	    {
	      unsigned char *buf = alloca (dfa->mb_cur_max), *p;
	      wchar_t wc;
	      mbstate_t state;

	      p = buf;
	      *p++ = dfa->nodes[node].opr.c;
	      while (++node < dfa->nodes_len
		     &&	dfa->nodes[node].type == CHARACTER
		     && dfa->nodes[node].mb_partial)
		*p++ = dfa->nodes[node].opr.c;
	      memset (&state, '\0', sizeof (state));
	      if (__mbrtowc (&wc, (const char *) buf, p - buf,
			     &state) == p - buf
		  && (__wcrtomb ((char *) buf, towlower (wc), &state)
		      != (size_t) -1))
		re_set_fastmap (fastmap, 0, buf[0]);
	    }
#endif
	}
      else if (type == SIMPLE_BRACKET)
	{
	  int i, ch;
	  for (i = 0, ch = 0; i < BITSET_WORDS; ++i)
	    {
	      int j;
	      bitset_word_t w = dfa->nodes[node].opr.sbcset[i];
	      for (j = 0; j < BITSET_WORD_BITS; ++j, ++ch)
		if (w & ((bitset_word_t) 1 << j))
		  re_set_fastmap (fastmap, icase, ch);
	    }
	}
#ifdef RE_ENABLE_I18N
      else if (type == COMPLEX_BRACKET)
	{
	  re_charset_t *cset = dfa->nodes[node].opr.mbcset;
	  int i;

# ifdef _LIBC
	  /* See if we have to try all bytes which start multiple collation
	     elements.
	     e.g. In da_DK, we want to catch 'a' since "aa" is a valid
		  collation element, and don't catch 'b' since 'b' is
		  the only collation element which starts from 'b' (and
		  it is caught by SIMPLE_BRACKET).  */
	      if (_NL_CURRENT_WORD (LC_COLLATE, _NL_COLLATE_NRULES) != 0
		  && (cset->ncoll_syms || cset->nranges))
		{
		  const int32_t *table = (const int32_t *)
		    _NL_CURRENT (LC_COLLATE, _NL_COLLATE_TABLEMB);
		  for (i = 0; i < SBC_MAX; ++i)
		    if (table[i] < 0)
		      re_set_fastmap (fastmap, icase, i);
		}
# endif /* _LIBC */

	  /* See if we have to start the match at all multibyte characters,
	     i.e. where we would not find an invalid sequence.  This only
	     applies to multibyte character sets; for single byte character
	     sets, the SIMPLE_BRACKET again suffices.  */
	  if (dfa->mb_cur_max > 1
	      && (cset->nchar_classes || cset->non_match || cset->nranges
# ifdef _LIBC
		  || cset->nequiv_classes
# endif /* _LIBC */
		 ))
	    {
	      unsigned char c = 0;
	      do
		{
		  mbstate_t mbs;
		  memset (&mbs, 0, sizeof (mbs));
		  if (__mbrtowc (NULL, (char *) &c, 1, &mbs) == (size_t) -2)
		    re_set_fastmap (fastmap, false, (int) c);
		}
	      while (++c != 0);
	    }

	  else
	    {
	      /* ... Else catch all bytes which can start the mbchars.  */
	      for (i = 0; i < cset->nmbchars; ++i)
		{
		  char buf[256];
		  mbstate_t state;
		  memset (&state, '\0', sizeof (state));
		  if (__wcrtomb (buf, cset->mbchars[i], &state) != (size_t) -1)
		    re_set_fastmap (fastmap, icase, *(unsigned char *) buf);
		  if ((bufp->syntax & RE_ICASE) && dfa->mb_cur_max > 1)
		    {
		      if (__wcrtomb (buf, towlower (cset->mbchars[i]), &state)
			  != (size_t) -1)
			re_set_fastmap (fastmap, false, *(unsigned char *) buf);
		    }
		}
	    }
	}
#endif /* RE_ENABLE_I18N */
      else if (type == OP_PERIOD
#ifdef RE_ENABLE_I18N
	       || type == OP_UTF8_PERIOD
#endif /* RE_ENABLE_I18N */
	       || type == END_OF_RE)
	{
	  memset (fastmap, '\1', sizeof (char) * SBC_MAX);
	  if (type == END_OF_RE)
	    bufp->can_be_null = 1;
	  return;
	}
    }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
struct kwsmatch {scalar_t__ index; } ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  mbs ;
struct TYPE_7__ {int* end; } ;
struct TYPE_6__ {int not_eol; } ;
struct TYPE_8__ {TYPE_2__ regs; TYPE_1__ regexbuf; } ;

/* Variables and functions */
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  WCHAR (unsigned char) ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  dfa ; 
 size_t dfaexec (int /*<<< orphan*/ *,char const*,int,int*) ; 
 char eolbyte ; 
 char* getenv (char*) ; 
 scalar_t__ iswalnum (int) ; 
 scalar_t__ kwset ; 
 scalar_t__ kwset_exact_matches ; 
 size_t kwsexec (scalar_t__,char const*,int,struct kwsmatch*) ; 
 scalar_t__ match_icase ; 
 scalar_t__ match_lines ; 
 scalar_t__ match_words ; 
 size_t mbrlen (char const*,size_t,int /*<<< orphan*/ *) ; 
 size_t mbrtowc (int*,char const*,int,int /*<<< orphan*/ *) ; 
 int mbtowc (int*,char const*,int) ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 TYPE_5__* patterns ; 
 size_t pcount ; 
 int re_match (TYPE_1__*,char const*,int,int,TYPE_2__*) ; 
 int re_search (TYPE_1__*,char const*,int,int,int,TYPE_2__*) ; 
 scalar_t__ using_utf8 ; 

__attribute__((used)) static size_t
EGexecute (char const *buf, size_t size, size_t *match_size, int exact)
{
  register char const *buflim, *beg, *end;
  char eol = eolbyte;
  int backref;
  ptrdiff_t start, len;
  struct kwsmatch kwsm;
  size_t i, ret_val;
  static int use_dfa;
  static int use_dfa_checked = 0;
#ifdef MBS_SUPPORT
  const char *last_char = NULL;
  int mb_cur_max = MB_CUR_MAX;
  mbstate_t mbs;
  memset (&mbs, '\0', sizeof (mbstate_t));
#endif /* MBS_SUPPORT */

  if (!use_dfa_checked)
    {
      char *grep_use_dfa = getenv ("GREP_USE_DFA");
      if (!grep_use_dfa)
	{
#ifdef MBS_SUPPORT
	  /* Turn off DFA when processing multibyte input. */
	  use_dfa = (MB_CUR_MAX == 1);
#else
	  use_dfa = 1;
#endif /* MBS_SUPPORT */
	}
      else
	{
	  use_dfa = atoi (grep_use_dfa);
	}

      use_dfa_checked = 1;
    }

  buflim = buf + size;

  for (beg = end = buf; end < buflim; beg = end)
    {
      if (!exact)
	{
	  if (kwset)
	    {
	      /* Find a possible match using the KWset matcher. */
#ifdef MBS_SUPPORT
	      size_t bytes_left = 0;
#endif /* MBS_SUPPORT */
	      size_t offset;
#ifdef MBS_SUPPORT
	      /* kwsexec doesn't work with match_icase and multibyte input. */
	      if (match_icase && mb_cur_max > 1)
		/* Avoid kwset */
		offset = 0;
	      else
#endif /* MBS_SUPPORT */
	      offset = kwsexec (kwset, beg, buflim - beg, &kwsm);
	      if (offset == (size_t) -1)
	        goto failure;
#ifdef MBS_SUPPORT
	      if (mb_cur_max > 1 && !using_utf8)
		{
		  bytes_left = offset;
		  while (bytes_left)
		    {
		      size_t mlen = mbrlen (beg, bytes_left, &mbs);

		      last_char = beg;
		      if (mlen == (size_t) -1 || mlen == 0)
			{
			  /* Incomplete character: treat as single-byte. */
			  memset (&mbs, '\0', sizeof (mbstate_t));
			  beg++;
			  bytes_left--;
			  continue;
			}

		      if (mlen == (size_t) -2)
			{
			  /* Offset points inside multibyte character:
			   * no good. */
			  memset (&mbs, '\0', sizeof (mbstate_t));
			  break;
			}

		      beg += mlen;
		      bytes_left -= mlen;
		    }
		}
	      else
#endif /* MBS_SUPPORT */
	      beg += offset;
	      /* Narrow down to the line containing the candidate, and
		 run it through DFA. */
	      end = memchr(beg, eol, buflim - beg);
	      end++;
#ifdef MBS_SUPPORT
	      if (mb_cur_max > 1 && bytes_left)
		continue;
#endif /* MBS_SUPPORT */
	      while (beg > buf && beg[-1] != eol)
		--beg;
	      if (
#ifdef MBS_SUPPORT
		  !(match_icase && mb_cur_max > 1) &&
#endif /* MBS_SUPPORT */
		  (kwsm.index < kwset_exact_matches))
		goto success_in_beg_and_end;
	      if (use_dfa &&
		  dfaexec (&dfa, beg, end - beg, &backref) == (size_t) -1)
		continue;
	    }
	  else
	    {
	      /* No good fixed strings; start with DFA. */
#ifdef MBS_SUPPORT
	      size_t bytes_left = 0;
#endif /* MBS_SUPPORT */
	      size_t offset = 0;
	      if (use_dfa)
		offset = dfaexec (&dfa, beg, buflim - beg, &backref);
	      if (offset == (size_t) -1)
		break;
	      /* Narrow down to the line we've found. */
#ifdef MBS_SUPPORT
	      if (mb_cur_max > 1 && !using_utf8)
		{
		  bytes_left = offset;
		  while (bytes_left)
		    {
		      size_t mlen = mbrlen (beg, bytes_left, &mbs);

		      last_char = beg;
		      if (mlen == (size_t) -1 || mlen == 0)
			{
			  /* Incomplete character: treat as single-byte. */
			  memset (&mbs, '\0', sizeof (mbstate_t));
			  beg++;
			  bytes_left--;
			  continue;
			}

		      if (mlen == (size_t) -2)
			{
			  /* Offset points inside multibyte character:
			   * no good. */
			  memset (&mbs, '\0', sizeof (mbstate_t));
			  break;
			}

		      beg += mlen;
		      bytes_left -= mlen;
		    }
		}
	      else
#endif /* MBS_SUPPORT */
	      beg += offset;
	      end = memchr (beg, eol, buflim - beg);
	      end++;
#ifdef MBS_SUPPORT
	      if (mb_cur_max > 1 && bytes_left)
		continue;
#endif /* MBS_SUPPORT */
	      while (beg > buf && beg[-1] != eol)
		--beg;
	    }
	  /* Successful, no backreferences encountered! */
	  if (use_dfa && !backref)
	    goto success_in_beg_and_end;
	}
      else
	end = beg + size;

      /* If we've made it to this point, this means DFA has seen
	 a probable match, and we need to run it through Regex. */
      for (i = 0; i < pcount; i++)
	{
	  patterns[i].regexbuf.not_eol = 0;
	  if (0 <= (start = re_search (&(patterns[i].regexbuf), beg,
				       end - beg - 1, 0,
				       end - beg - 1, &(patterns[i].regs))))
	    {
	      len = patterns[i].regs.end[0] - start;
	      if (exact && !match_words)
	        goto success_in_start_and_len;
	      if ((!match_lines && !match_words)
		  || (match_lines && len == end - beg - 1))
		goto success_in_beg_and_end;
	      /* If -w, check if the match aligns with word boundaries.
		 We do this iteratively because:
		 (a) the line may contain more than one occurence of the
		 pattern, and
		 (b) Several alternatives in the pattern might be valid at a
		 given point, and we may need to consider a shorter one to
		 find a word boundary.  */
	      if (match_words)
		while (start >= 0)
		  {
		    int lword_match = 0;
		    if (start == 0)
		      lword_match = 1;
		    else
		      {
			assert (start > 0);
#ifdef MBS_SUPPORT
			if (mb_cur_max > 1)
			  {
			    const char *s;
			    size_t mr;
			    wchar_t pwc;

			    /* Locate the start of the multibyte character
			       before the match position (== beg + start).  */
			    if (using_utf8)
			      {
				/* UTF-8 is a special case: scan backwards
				   until we find a 7-bit character or a
				   lead byte.  */
				s = beg + start - 1;
				while (s > buf
				       && (unsigned char) *s >= 0x80
				       && (unsigned char) *s <= 0xbf)
				  --s;
			      }
			    else
			      {
				/* Scan forwards to find the start of the
				   last complete character before the
				   match position.  */
				size_t bytes_left = start - 1;
				s = beg;
				while (bytes_left > 0)
				  {
				    mr = mbrlen (s, bytes_left, &mbs);
				    if (mr == (size_t) -1 || mr == 0)
				      {
					memset (&mbs, '\0', sizeof (mbs));
					s++;
					bytes_left--;
					continue;
				      }
				    if (mr == (size_t) -2)
				      {
					memset (&mbs, '\0', sizeof (mbs));
					break;
				      }
				    s += mr;
				    bytes_left -= mr;
				  }
			      }
			    mr = mbrtowc (&pwc, s, beg + start - s, &mbs);
			    if (mr == (size_t) -2 || mr == (size_t) -1 ||
				mr == 0)
			      {
				memset (&mbs, '\0', sizeof (mbstate_t));
				lword_match = 1;
			      }
			    else if (!(iswalnum (pwc) || pwc == L'_')
				     && mr == beg + start - s)
			      lword_match = 1;
			  }
			else
#endif /* MBS_SUPPORT */
			if (!WCHAR ((unsigned char) beg[start - 1]))
			  lword_match = 1;
		      }

		    if (lword_match)
		      {
			int rword_match = 0;
			if (start + len == end - beg - 1)
			  rword_match = 1;
			else
			  {
#ifdef MBS_SUPPORT
			    if (mb_cur_max > 1)
			      {
				wchar_t nwc;
				int mr;

				mr = mbtowc (&nwc, beg + start + len,
					     end - beg - start - len - 1);
				if (mr <= 0)
				  {
				    memset (&mbs, '\0', sizeof (mbstate_t));
				    rword_match = 1;
				  }
				else if (!iswalnum (nwc) && nwc != L'_')
				  rword_match = 1;
			      }
			    else
#endif /* MBS_SUPPORT */
			    if (!WCHAR ((unsigned char) beg[start + len]))
			      rword_match = 1;
			  }

			if (rword_match)
			  {
			    if (!exact)
			      /* Returns the whole line. */
			      goto success_in_beg_and_end;
			    else
			      /* Returns just this word match. */
			      goto success_in_start_and_len;
			  }
		      }
		    if (len > 0)
		      {
			/* Try a shorter length anchored at the same place. */
			--len;
			patterns[i].regexbuf.not_eol = 1;
			len = re_match (&(patterns[i].regexbuf), beg,
					start + len, start,
					&(patterns[i].regs));
		      }
		    if (len <= 0)
		      {
			/* Try looking further on. */
			if (start == end - beg - 1)
			  break;
			++start;
			patterns[i].regexbuf.not_eol = 0;
			start = re_search (&(patterns[i].regexbuf), beg,
					   end - beg - 1,
					   start, end - beg - 1 - start,
					   &(patterns[i].regs));
			len = patterns[i].regs.end[0] - start;
		      }
		  }
	    }
	} /* for Regex patterns.  */
    } /* for (beg = end ..) */

 failure:
  return (size_t) -1;

 success_in_beg_and_end:
  len = end - beg;
  start = beg - buf;
  /* FALLTHROUGH */

 success_in_start_and_len:
  *match_size = len;
  return start;
}
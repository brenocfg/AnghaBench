#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int wchar_t ;
struct kwsmatch {size_t* size; } ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 scalar_t__ Fimbexec (char const*,size_t,size_t*,int) ; 
 int MB_CUR_MAX ; 
 scalar_t__ WCHAR (unsigned char) ; 
 char eolbyte ; 
 scalar_t__ f_i_multibyte ; 
 scalar_t__ iswalnum (int) ; 
 int /*<<< orphan*/  kwset ; 
 size_t kwsexec (int /*<<< orphan*/ ,char const*,size_t,struct kwsmatch*) ; 
 scalar_t__ match_lines ; 
 scalar_t__ match_words ; 
 size_t mbrlen (char const*,int,int /*<<< orphan*/ *) ; 
 int mbtowc (int*,char const*,int) ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 scalar_t__ using_utf8 ; 

__attribute__((used)) static size_t
Fexecute (char const *buf, size_t size, size_t *match_size, int exact)
{
  register char const *beg, *try, *end;
  register size_t len;
  char eol = eolbyte;
  struct kwsmatch kwsmatch;
  size_t ret_val;
#ifdef MBS_SUPPORT
  int mb_cur_max = MB_CUR_MAX;
  mbstate_t mbs;
  memset (&mbs, '\0', sizeof (mbstate_t));
  const char *last_char = NULL;
#endif /* MBS_SUPPORT */

  for (beg = buf; beg <= buf + size; ++beg)
    {
      size_t offset;
      offset = kwsexec (kwset, beg, buf + size - beg, &kwsmatch);

      if (offset == (size_t) -1)
	goto failure;
#ifdef MBS_SUPPORT
      if (mb_cur_max > 1 && !using_utf8)
	{
	  size_t bytes_left = offset;
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
		  /* Offset points inside multibyte character: no good. */
		  memset (&mbs, '\0', sizeof (mbstate_t));
		  break;
		}

	      beg += mlen;
	      bytes_left -= mlen;
	    }

	  if (bytes_left)
	    {
	      beg += bytes_left;
	      continue;
	    }
	}
      else
#endif /* MBS_SUPPORT */
      beg += offset;
#ifdef MBS_SUPPORT
      /* For f_i_multibyte, the string at beg now matches first 3 chars of
	 one of the search strings (less if there are shorter search strings).
	 See if this is a real match.  */
      if (f_i_multibyte
	  && Fimbexec (beg, buf + size - beg, &kwsmatch.size[0], exact))
	goto next_char;
#endif /* MBS_SUPPORT */
      len = kwsmatch.size[0];
      if (exact && !match_words)
	goto success_in_beg_and_len;
      if (match_lines)
	{
	  if (beg > buf && beg[-1] != eol)
	    goto next_char;
	  if (beg + len < buf + size && beg[len] != eol)
	    goto next_char;
	  goto success;
	}
      else if (match_words)
	{
	  while (1)
	    {
	      int word_match = 0;
	      if (beg > buf)
		{
#ifdef MBS_SUPPORT
		  if (mb_cur_max > 1)
		    {
		      const char *s;
		      int mr;
		      wchar_t pwc;

		      if (using_utf8)
			{
			  s = beg - 1;
			  while (s > buf
				 && (unsigned char) *s >= 0x80
				 && (unsigned char) *s <= 0xbf)
			    --s;
			}
		      else
			s = last_char;
		      mr = mbtowc (&pwc, s, beg - s);
		      if (mr <= 0)
			memset (&mbs, '\0', sizeof (mbstate_t));
		      else if ((iswalnum (pwc) || pwc == L'_')
			       && mr == (int) (beg - s))
			goto next_char;
		    }
		  else
#endif /* MBS_SUPPORT */
		  if (WCHAR ((unsigned char) beg[-1]))
		    goto next_char;
		}
#ifdef MBS_SUPPORT
	      if (mb_cur_max > 1)
		{
		  wchar_t nwc;
		  int mr;

		  mr = mbtowc (&nwc, beg + len, buf + size - beg - len);
		  if (mr <= 0)
		    {
		      memset (&mbs, '\0', sizeof (mbstate_t));
		      word_match = 1;
		    }
		  else if (!iswalnum (nwc) && nwc != L'_')
		    word_match = 1;
		}
	      else
#endif /* MBS_SUPPORT */
		if (beg + len >= buf + size || !WCHAR ((unsigned char) beg[len]))
		  word_match = 1;
	      if (word_match)
		{
		  if (!exact)
		    /* Returns the whole line now we know there's a word match. */
		    goto success;
		  else
		    /* Returns just this word match. */
		    goto success_in_beg_and_len;
		}
	      if (len > 0)
		{
		  /* Try a shorter length anchored at the same place. */
		  --len;
		  offset = kwsexec (kwset, beg, len, &kwsmatch);

		  if (offset == -1)
		    goto next_char; /* Try a different anchor. */
#ifdef MBS_SUPPORT
		  if (mb_cur_max > 1 && !using_utf8)
		    {
		      size_t bytes_left = offset;
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

		      if (bytes_left)
			{
			  memset (&mbs, '\0', sizeof (mbstate_t));
			  goto next_char; /* Try a different anchor. */
			}
		    }
		  else
#endif /* MBS_SUPPORT */
		  beg += offset;
#ifdef MBS_SUPPORT
		  /* The string at beg now matches first 3 chars of one of
		     the search strings (less if there are shorter search
		     strings).  See if this is a real match.  */
		  if (f_i_multibyte
		      && Fimbexec (beg, len - offset, &kwsmatch.size[0],
				   exact))
		    goto next_char;
#endif /* MBS_SUPPORT */
		  len = kwsmatch.size[0];
		}
	    }
	}
      else
	goto success;
next_char:;
#ifdef MBS_SUPPORT
      /* Advance to next character.  For MB_CUR_MAX == 1 case this is handled
	 by ++beg above.  */
      if (mb_cur_max > 1)
	{
	  if (using_utf8)
	    {
	      unsigned char c = *beg;
	      if (c >= 0xc2)
		{
		  if (c < 0xe0)
		    ++beg;
		  else if (c < 0xf0)
		    beg += 2;
		  else if (c < 0xf8)
		    beg += 3;
		  else if (c < 0xfc)
		    beg += 4;
		  else if (c < 0xfe)
		    beg += 5;
		}
	    }
	  else
	    {
	      size_t l = mbrlen (beg, buf + size - beg, &mbs);

	      last_char = beg;
	      if (l + 2 >= 2)
		beg += l - 1;
	      else
		memset (&mbs, '\0', sizeof (mbstate_t));
	    }
	}
#endif /* MBS_SUPPORT */
    }

 failure:
  return -1;

 success:
#ifdef MBS_SUPPORT
  if (mb_cur_max > 1 && !using_utf8)
    {
      end = beg + len;
      while (end < buf + size)
	{
	  size_t mlen = mbrlen (end, buf + size - end, &mbs);
	  if (mlen == (size_t) -1 || mlen == (size_t) -2 || mlen == 0)
	    {
	      memset (&mbs, '\0', sizeof (mbstate_t));
	      mlen = 1;
	    }
	  if (mlen == 1 && *end == eol)
	    break;

	  end += mlen;
	}
    }
  else
#endif /* MBS_SUPPORT */
  end = memchr (beg + len, eol, (buf + size) - (beg + len));

  end++;
  while (buf < beg && beg[-1] != eol)
    --beg;
  len = end - beg;
  /* FALLTHROUGH */

 success_in_beg_and_len:
  *match_size = len;
  return beg - buf;
}
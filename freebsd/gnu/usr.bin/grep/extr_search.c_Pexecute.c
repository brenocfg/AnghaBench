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

/* Variables and functions */
#define  PCRE_ERROR_NOMATCH 129 
#define  PCRE_ERROR_NOMEMORY 128 
 char* _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  cre ; 
 char eolbyte ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  extra ; 
 char* memchr (char const*,char,int) ; 
 int pcre_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static size_t
Pexecute (char const *buf, size_t size, size_t *match_size, int exact)
{
#if !HAVE_LIBPCRE
  abort ();
  return -1;
#else
  /* This array must have at least two elements; everything after that
     is just for performance improvement in pcre_exec.  */
  int sub[300];

  int e = pcre_exec (cre, extra, buf, size, 0, 0,
		     sub, sizeof sub / sizeof *sub);

  if (e <= 0)
    {
      switch (e)
	{
	case PCRE_ERROR_NOMATCH:
	  return -1;

	case PCRE_ERROR_NOMEMORY:
	  error (2, 0, _("Memory exhausted"));

	default:
	  abort ();
	}
    }
  else
    {
      /* Narrow down to the line we've found.  */
      char const *beg = buf + sub[0];
      char const *end = buf + sub[1];
      char const *buflim = buf + size;
      char eol = eolbyte;
      if (!exact)
	{
	  end = memchr (end, eol, buflim - end);
	  end++;
	  while (buf < beg && beg[-1] != eol)
	    --beg;
	}

      *match_size = end - beg;
      return beg - buf;
    }
#endif
}
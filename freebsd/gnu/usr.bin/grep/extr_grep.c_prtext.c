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
 int after_last_match ; 
 char const* bufbeg ; 
 char const* buflim ; 
 int bufoffset ; 
 char eolbyte ; 
 char const* lastout ; 
 char* memchr (char const*,char,int) ; 
 scalar_t__ out_after ; 
 int out_before ; 
 scalar_t__ out_quiet ; 
 int outleft ; 
 scalar_t__ pending ; 
 int /*<<< orphan*/  prline (char const*,char const*,char) ; 
 int /*<<< orphan*/  prpending (char const*) ; 
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static void
prtext (char const *beg, char const *lim, int *nlinesp)
{
  static int used;		/* avoid printing "--" before any output */
  char const *bp, *p;
  char eol = eolbyte;
  int i, n;

  if (!out_quiet && pending > 0)
    prpending (beg);

  p = beg;

  if (!out_quiet)
    {
      /* Deal with leading context crap. */

      bp = lastout ? lastout : bufbeg;
      for (i = 0; i < out_before; ++i)
	if (p > bp)
	  do
	    --p;
	  while (p[-1] != eol);

      /* We only print the "--" separator if our output is
	 discontiguous from the last output in the file. */
      if ((out_before || out_after) && used && p != lastout)
	puts ("--");

      while (p < beg)
	{
	  char const *nl = memchr (p, eol, beg - p);
	  nl++;
	  prline (p, nl, '-');
	  p = nl;
	}
    }

  if (nlinesp)
    {
      /* Caller wants a line count. */
      for (n = 0; p < lim && n < outleft; n++)
	{
	  char const *nl = memchr (p, eol, lim - p);
	  nl++;
	  if (!out_quiet)
	    prline (p, nl, ':');
	  p = nl;
	}
      *nlinesp = n;

      /* relying on it that this function is never called when outleft = 0.  */
      after_last_match = bufoffset - (buflim - p);
    }
  else
    if (!out_quiet)
      prline (beg, lim, ':');

  pending = out_quiet ? 0 : out_after;
  used = 1;
}
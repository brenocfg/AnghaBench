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
struct dfa {scalar_t__ nregexps; scalar_t__ nleaves; scalar_t__ depth; scalar_t__ tindex; scalar_t__ cindex; } ;

/* Variables and functions */
 scalar_t__ ISUPPER (unsigned char) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int case_fold ; 
 int /*<<< orphan*/  dfaanalyze (struct dfa*,int) ; 
 int /*<<< orphan*/  dfaerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfainit (struct dfa*) ; 
 int /*<<< orphan*/  dfamust (struct dfa*) ; 
 int /*<<< orphan*/  dfaparse (char const*,size_t,struct dfa*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 char tolower (unsigned char) ; 

void
dfacomp (char const *s, size_t len, struct dfa *d, int searchflag)
{
  if (case_fold)	/* dummy folding in service of dfamust() */
    {
      char *lcopy;
      int i;

      lcopy = malloc(len);
      if (!lcopy)
	dfaerror(_("out of memory"));

      /* This is a kludge. */
      case_fold = 0;
      for (i = 0; i < len; ++i)
	if (ISUPPER ((unsigned char) s[i]))
	  lcopy[i] = tolower ((unsigned char) s[i]);
	else
	  lcopy[i] = s[i];

      dfainit(d);
      dfaparse(lcopy, len, d);
      free(lcopy);
      dfamust(d);
      d->cindex = d->tindex = d->depth = d->nleaves = d->nregexps = 0;
      case_fold = 1;
      dfaparse(s, len, d);
      dfaanalyze(d, searchflag);
    }
  else
    {
        dfainit(d);
        dfaparse(s, len, d);
	dfamust(d);
        dfaanalyze(d, searchflag);
    }
}
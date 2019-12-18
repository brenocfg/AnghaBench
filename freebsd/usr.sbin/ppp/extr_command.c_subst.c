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
 int /*<<< orphan*/  bcopy (char const*,char*,int) ; 
 char* realloc (char*,int) ; 
 int strlen (char const*) ; 
 char* strstrword (char*,char const*) ; 

__attribute__((used)) static char *
subst(char *tgt, const char *oldstr, const char *newstr)
{
  /* tgt is a malloc()d area... realloc() as necessary */
  char *word, *ntgt;
  int ltgt, loldstr, lnewstr, pos;

  if ((word = strstrword(tgt, oldstr)) == NULL)
    return tgt;

  ltgt = strlen(tgt) + 1;
  loldstr = strlen(oldstr);
  lnewstr = strlen(newstr);
  do {
    pos = word - tgt;
    if (loldstr > lnewstr)
      bcopy(word + loldstr, word + lnewstr, ltgt - pos - loldstr);
    if (loldstr != lnewstr) {
      ntgt = realloc(tgt, ltgt += lnewstr - loldstr);
      if (ntgt == NULL)
        break;			/* Oh wonderful ! */
      word = ntgt + pos;
      tgt = ntgt;
    }
    if (lnewstr > loldstr)
      bcopy(word + loldstr, word + lnewstr, ltgt - pos - lnewstr);
    bcopy(newstr, word, lnewstr);
  } while ((word = strstrword(word, oldstr)));

  return tgt;
}
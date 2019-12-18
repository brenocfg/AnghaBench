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
 int PCRE_CASELESS ; 
 int PCRE_MULTILINE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  cre ; 
 char eolbyte ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  extra ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ match_icase ; 
 scalar_t__ match_lines ; 
 scalar_t__ match_words ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  pcre_compile (char*,int,char const**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcre_maketables () ; 
 int /*<<< orphan*/  pcre_study (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void
Pcompile (char const *pattern, size_t size)
{
#if !HAVE_LIBPCRE
  error (2, 0, _("The -P option is not supported"));
#else
  int e;
  char const *ep;
  char *re = xmalloc (4 * size + 7);
  int flags = PCRE_MULTILINE | (match_icase ? PCRE_CASELESS : 0);
  char const *patlim = pattern + size;
  char *n = re;
  char const *p;
  char const *pnul;

  /* FIXME: Remove this restriction.  */
  if (eolbyte != '\n')
    error (2, 0, _("The -P and -z options cannot be combined"));

  *n = '\0';
  if (match_lines)
    strcpy (n, "^(");
  if (match_words)
    strcpy (n, "\\b(");
  n += strlen (n);

  /* The PCRE interface doesn't allow NUL bytes in the pattern, so
     replace each NUL byte in the pattern with the four characters
     "\000", removing a preceding backslash if there are an odd
     number of backslashes before the NUL.

     FIXME: This method does not work with some multibyte character
     encodings, notably Shift-JIS, where a multibyte character can end
     in a backslash byte.  */
  for (p = pattern; (pnul = memchr (p, '\0', patlim - p)); p = pnul + 1)
    {
      memcpy (n, p, pnul - p);
      n += pnul - p;
      for (p = pnul; pattern < p && p[-1] == '\\'; p--)
	continue;
      n -= (pnul - p) & 1;
      strcpy (n, "\\000");
      n += 4;
    }

  memcpy (n, p, patlim - p);
  n += patlim - p;
  *n = '\0';
  if (match_words)
    strcpy (n, ")\\b");
  if (match_lines)
    strcpy (n, ")$");

  cre = pcre_compile (re, flags, &ep, &e, pcre_maketables ());
  if (!cre)
    error (2, 0, ep);

  extra = pcre_study (cre, 0, &ep);
  if (ep)
    error (2, 0, ep);

  free (re);
#endif
}
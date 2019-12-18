#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  regexbuf; } ;

/* Variables and functions */
 int RE_ICASE ; 
 int RE_SYNTAX_AWK ; 
 int RE_SYNTAX_POSIX_EGREP ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  check_utf8 () ; 
 int /*<<< orphan*/  dfa ; 
 int /*<<< orphan*/  dfacomp (char const*,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dfasyntax (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eolbyte ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  kwsmusts () ; 
 scalar_t__ match_icase ; 
 scalar_t__ match_lines ; 
 scalar_t__ match_words ; 
 int /*<<< orphan*/  matcher ; 
 char* memchr (char const*,char,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 TYPE_1__* patterns ; 
 TYPE_1__ patterns0 ; 
 int pcount ; 
 char* re_compile_pattern (char const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  re_set_syntax (int) ; 
 TYPE_1__* realloc (TYPE_1__*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char*) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void
Ecompile (char const *pattern, size_t size)
{
  const char *err;
  const char *sep;
  size_t total = size;
  char const *motif = pattern;

  check_utf8 ();
  if (strcmp (matcher, "awk") == 0)
    {
      re_set_syntax (RE_SYNTAX_AWK | (match_icase ? RE_ICASE : 0));
      dfasyntax (RE_SYNTAX_AWK, match_icase, eolbyte);
    }
  else
    {
      re_set_syntax (RE_SYNTAX_POSIX_EGREP | (match_icase ? RE_ICASE : 0));
      dfasyntax (RE_SYNTAX_POSIX_EGREP, match_icase, eolbyte);
    }

  /* For GNU regex compiler we have to pass the patterns separately to detect
     errors like "[\nallo\n]\n".  The patterns here are "[", "allo" and "]"
     GNU regex should have raise a syntax error.  The same for backref, where
     the backref should have been local to each pattern.  */
  do
    {
      size_t len;
      sep = memchr (motif, '\n', total);
      if (sep)
	{
	  len = sep - motif;
	  sep++;
	  total -= (len + 1);
	}
      else
	{
	  len = total;
	  total = 0;
	}

      patterns = realloc (patterns, (pcount + 1) * sizeof (*patterns));
      if (patterns == NULL)
	error (2, errno, _("memory exhausted"));
      patterns[pcount] = patterns0;

      if ((err = re_compile_pattern (motif, len,
				    &(patterns[pcount].regexbuf))) != 0)
	error (2, 0, err);
      pcount++;

      motif = sep;
    } while (sep && total != 0);

  /* In the match_words and match_lines cases, we use a different pattern
     for the DFA matcher that will quickly throw out cases that won't work.
     Then if DFA succeeds we do some hairy stuff using the regex matcher
     to decide whether the match should really count. */
  if (match_words || match_lines)
    {
      /* In the whole-word case, we use the pattern:
	 (^|[^[:alnum:]_])(userpattern)([^[:alnum:]_]|$).
	 In the whole-line case, we use the pattern:
	 ^(userpattern)$.  */

      static char const line_beg[] = "^(";
      static char const line_end[] = ")$";
      static char const word_beg[] = "(^|[^[:alnum:]_])(";
      static char const word_end[] = ")([^[:alnum:]_]|$)";
      char *n = xmalloc (sizeof word_beg - 1 + size + sizeof word_end);
      size_t i;
      strcpy (n, match_lines ? line_beg : word_beg);
      i = strlen(n);
      memcpy (n + i, pattern, size);
      i += size;
      strcpy (n + i, match_lines ? line_end : word_end);
      i += strlen (n + i);
      pattern = n;
      size = i;
    }

  dfacomp (pattern, size, &dfa, 1);
  kwsmusts ();
}
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
typedef  int /*<<< orphan*/  wchar_t ;
struct quoting_options {int* quote_these_too; } ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  enum quoting_style { ____Placeholder_quoting_style } quoting_style ;

/* Variables and functions */
#define  ALERT_CHAR 134 
 unsigned char INT_BITS ; 
 int ISPRINT (unsigned char) ; 
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  STORE (char const) ; 
#define  c_quoting_style 133 
#define  clocale_quoting_style 132 
#define  escape_quoting_style 131 
 char* gettext_quote (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iswprint (int /*<<< orphan*/ ) ; 
#define  locale_quoting_style 130 
 size_t mbrtowc (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbsinit (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
#define  shell_always_quoting_style 129 
#define  shell_quoting_style 128 
 size_t strlen (char const*) ; 

__attribute__((used)) static size_t
quotearg_buffer_restyled (char *buffer, size_t buffersize,
			  char const *arg, size_t argsize,
			  enum quoting_style quoting_style,
			  struct quoting_options const *o)
{
  size_t i;
  size_t len = 0;
  char const *quote_string = 0;
  size_t quote_string_len = 0;
  int backslash_escapes = 0;
  int unibyte_locale = MB_CUR_MAX == 1;

#define STORE(c) \
    do \
      { \
	if (len < buffersize) \
	  buffer[len] = (c); \
	len++; \
      } \
    while (0)

  switch (quoting_style)
    {
    case c_quoting_style:
      STORE ('"');
      backslash_escapes = 1;
      quote_string = "\"";
      quote_string_len = 1;
      break;

    case escape_quoting_style:
      backslash_escapes = 1;
      break;

    case locale_quoting_style:
    case clocale_quoting_style:
      {
	/* Get translations for open and closing quotation marks.

	   The message catalog should translate "`" to a left
	   quotation mark suitable for the locale, and similarly for
	   "'".  If the catalog has no translation,
	   locale_quoting_style quotes `like this', and
	   clocale_quoting_style quotes "like this".

	   For example, an American English Unicode locale should
	   translate "`" to U+201C (LEFT DOUBLE QUOTATION MARK), and
	   should translate "'" to U+201D (RIGHT DOUBLE QUOTATION
	   MARK).  A British English Unicode locale should instead
	   translate these to U+2018 (LEFT SINGLE QUOTATION MARK) and
	   U+2019 (RIGHT SINGLE QUOTATION MARK), respectively.  */

	char const *left = gettext_quote (N_("`"), quoting_style);
	char const *right = gettext_quote (N_("'"), quoting_style);
	for (quote_string = left; *quote_string; quote_string++)
	  STORE (*quote_string);
	backslash_escapes = 1;
	quote_string = right;
	quote_string_len = strlen (quote_string);
      }
      break;

    case shell_always_quoting_style:
      STORE ('\'');
      quote_string = "'";
      quote_string_len = 1;
      break;

    default:
      break;
    }

  for (i = 0;  ! (argsize == (size_t) -1 ? arg[i] == '\0' : i == argsize);  i++)
    {
      unsigned char c;
      unsigned char esc;

      if (backslash_escapes
	  && quote_string_len
	  && i + quote_string_len <= argsize
	  && memcmp (arg + i, quote_string, quote_string_len) == 0)
	STORE ('\\');

      c = arg[i];
      switch (c)
	{
	case '?':
	  switch (quoting_style)
	    {
	    case shell_quoting_style:
	      goto use_shell_always_quoting_style;

	    case c_quoting_style:
	      if (i + 2 < argsize && arg[i + 1] == '?')
		switch (arg[i + 2])
		  {
		  case '!': case '\'':
		  case '(': case ')': case '-': case '/':
		  case '<': case '=': case '>':
		    /* Escape the second '?' in what would otherwise be
		       a trigraph.  */
		    i += 2;
		    c = arg[i + 2];
		    STORE ('?');
		    STORE ('\\');
		    STORE ('?');
		    break;
		  }
	      break;

	    default:
	      break;
	    }
	  break;

	case ALERT_CHAR: esc = 'a'; goto c_escape;
	case '\b': esc = 'b'; goto c_escape;
	case '\f': esc = 'f'; goto c_escape;
	case '\n': esc = 'n'; goto c_and_shell_escape;
	case '\r': esc = 'r'; goto c_and_shell_escape;
	case '\t': esc = 't'; goto c_and_shell_escape;
	case '\v': esc = 'v'; goto c_escape;
	case '\\': esc = c; goto c_and_shell_escape;

	c_and_shell_escape:
	  if (quoting_style == shell_quoting_style)
	    goto use_shell_always_quoting_style;
	c_escape:
	  if (backslash_escapes)
	    {
	      c = esc;
	      goto store_escape;
	    }
	  break;

	case '#': case '~':
	  if (i != 0)
	    break;
	  /* Fall through.  */
	case ' ':
	case '!': /* special in bash */
	case '"': case '$': case '&':
	case '(': case ')': case '*': case ';':
	case '<': case '>': case '[':
	case '^': /* special in old /bin/sh, e.g. SunOS 4.1.4 */
	case '`': case '|':
	  /* A shell special character.  In theory, '$' and '`' could
	     be the first bytes of multibyte characters, which means
	     we should check them with mbrtowc, but in practice this
	     doesn't happen so it's not worth worrying about.  */
	  if (quoting_style == shell_quoting_style)
	    goto use_shell_always_quoting_style;
	  break;

	case '\'':
	  switch (quoting_style)
	    {
	    case shell_quoting_style:
	      goto use_shell_always_quoting_style;

	    case shell_always_quoting_style:
	      STORE ('\'');
	      STORE ('\\');
	      STORE ('\'');
	      break;

	    default:
	      break;
	    }
	  break;

	case '%': case '+': case ',': case '-': case '.': case '/':
	case '0': case '1': case '2': case '3': case '4': case '5':
	case '6': case '7': case '8': case '9': case ':': case '=':
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
	case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
	case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
	case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
	case 'Y': case 'Z': case ']': case '_': case 'a': case 'b':
	case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
	case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
	case 'o': case 'p': case 'q': case 'r': case 's': case 't':
	case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
	case '{': case '}':
	  /* These characters don't cause problems, no matter what the
	     quoting style is.  They cannot start multibyte sequences.  */
	  break;

	default:
	  /* If we have a multibyte sequence, copy it until we reach
	     its end, find an error, or come back to the initial shift
	     state.  For C-like styles, if the sequence has
	     unprintable characters, escape the whole sequence, since
	     we can't easily escape single characters within it.  */
	  {
	    /* Length of multibyte sequence found so far.  */
	    size_t m;

	    int printable;

	    if (unibyte_locale)
	      {
		m = 1;
		printable = ISPRINT (c);
	      }
	    else
	      {
		mbstate_t mbstate;
		memset (&mbstate, 0, sizeof mbstate);

		m = 0;
		printable = 1;
		if (argsize == (size_t) -1)
		  argsize = strlen (arg);

		do
		  {
		    wchar_t w;
		    size_t bytes = mbrtowc (&w, &arg[i + m],
					    argsize - (i + m), &mbstate);
		    if (bytes == 0)
		      break;
		    else if (bytes == (size_t) -1)
		      {
			printable = 0;
			break;
		      }
		    else if (bytes == (size_t) -2)
		      {
			printable = 0;
			while (i + m < argsize && arg[i + m])
			  m++;
			break;
		      }
		    else
		      {
			if (! iswprint (w))
			  printable = 0;
			m += bytes;
		      }
		  }
		while (! mbsinit (&mbstate));
	      }

	    if (1 < m || (backslash_escapes && ! printable))
	      {
		/* Output a multibyte sequence, or an escaped
		   unprintable unibyte character.  */
		size_t ilim = i + m;

		for (;;)
		  {
		    if (backslash_escapes && ! printable)
		      {
			STORE ('\\');
			STORE ('0' + (c >> 6));
			STORE ('0' + ((c >> 3) & 7));
			c = '0' + (c & 7);
		      }
		    if (ilim <= i + 1)
		      break;
		    STORE (c);
		    c = arg[++i];
		  }

		goto store_c;
	      }
	  }
	}

      if (! (backslash_escapes
	     && o->quote_these_too[c / INT_BITS] & (1 << (c % INT_BITS))))
	goto store_c;

    store_escape:
      STORE ('\\');

    store_c:
      STORE (c);
    }

  if (quote_string)
    for (; *quote_string; quote_string++)
      STORE (*quote_string);

  if (len < buffersize)
    buffer[len] = '\0';
  return len;

 use_shell_always_quoting_style:
  return quotearg_buffer_restyled (buffer, buffersize, arg, argsize,
				   shell_always_quoting_style, o);
}
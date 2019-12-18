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
typedef  char wint_t ;
typedef  int /*<<< orphan*/  mbibuff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EILSEQ ; 
 int MB_LEN_MAX ; 
 int VIS_MIMESTYLE ; 
 int VIS_NOSLASH ; 
 char WEOF ; 
 scalar_t__ debug ; 
 int eflags ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  extra ; 
 scalar_t__ fold ; 
 int foldit (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  foldwidth ; 
 scalar_t__ getc (int /*<<< orphan*/ *) ; 
 char getwc (int /*<<< orphan*/ *) ; 
 scalar_t__ markeol ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ none ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  strsenvisx (char*,int,char*,int,int,int /*<<< orphan*/ ,int*) ; 
 int wctomb (char*,char) ; 

__attribute__((used)) static void
process(FILE *fp)
{
	static int col = 0;
	static char nul[] = "\0";
	char *cp = nul + 1;	/* so *(cp-1) starts out != '\n' */
	wint_t c, c1, rachar;
	char mbibuff[2 * MB_LEN_MAX + 1]; /* max space for 2 wchars */
	char buff[4 * MB_LEN_MAX + 1]; /* max encoding length for one char */
	int mbilen, cerr = 0, raerr = 0;
	
        /*
         * The input stream is considered to be multibyte characters.
         * The input loop will read this data inputing one character,
	 * possibly multiple bytes, at a time and converting each to
	 * a wide character wchar_t.
         *
	 * The vis(3) functions, however, require single either bytes
	 * or a multibyte string as their arguments.  So we convert
	 * our input wchar_t and the following look-ahead wchar_t to
	 * a multibyte string for processing by vis(3).
         */

	/* Read one multibyte character, store as wchar_t */
	c = getwc(fp);
	if (c == WEOF && errno == EILSEQ) {
		/* Error in multibyte data.  Read one byte. */
		c = (wint_t)getc(fp);
		cerr = 1;
	}
	while (c != WEOF) {
		/* Clear multibyte input buffer. */
		memset(mbibuff, 0, sizeof(mbibuff));
		/* Read-ahead next multibyte character. */
		if (!cerr)
			rachar = getwc(fp);
		if (cerr || (rachar == WEOF && errno == EILSEQ)) {
			/* Error in multibyte data.  Read one byte. */
			rachar = (wint_t)getc(fp);
			raerr = 1;
		}
		if (none) {
			/* Handle -n flag. */
			cp = buff;
			*cp++ = c;
			if (c == '\\')
				*cp++ = '\\';
			*cp = '\0';
		} else if (markeol && c == '\n') {
			/* Handle -l flag. */
			cp = buff;
			if ((eflags & VIS_NOSLASH) == 0)
				*cp++ = '\\';
			*cp++ = '$';
			*cp++ = '\n';
			*cp = '\0';
		} else {
			/*
			 * Convert character using vis(3) library.
			 * At this point we will process one character.
			 * But we must pass the vis(3) library this
			 * character plus the next one because the next
			 * one is used as a look-ahead to decide how to
			 * encode this one under certain circumstances.
			 *
			 * Since our characters may be multibyte, e.g.,
			 * in the UTF-8 locale, we cannot use vis() and
			 * svis() which require byte input, so we must
			 * create a multibyte string and use strvisx().
			 */
			/* Treat EOF as a NUL char. */
			c1 = rachar;
			if (c1 == WEOF)
				c1 = L'\0';
			/*
			 * If we hit a multibyte conversion error above,
			 * insert byte directly into string buff because
			 * wctomb() will fail.  Else convert wchar_t to
			 * multibyte using wctomb().
			 */
			if (cerr) {
				*mbibuff = (char)c;
				mbilen = 1;
			} else
				mbilen = wctomb(mbibuff, c);
			/* Same for look-ahead character. */
			if (raerr)
				mbibuff[mbilen] = (char)c1;
			else
				wctomb(mbibuff + mbilen, c1);
			/* Perform encoding on just first character. */
			(void) strsenvisx(buff, 4 * MB_LEN_MAX, mbibuff,
			    1, eflags, extra, &cerr);
		}

		cp = buff;
		if (fold) {
#ifdef DEBUG
			if (debug)
				(void)printf("<%02d,", col);
#endif
			col = foldit(cp, col, foldwidth, eflags);
#ifdef DEBUG
			if (debug)
				(void)printf("%02d>", col);
#endif
		}
		do {
			(void)putchar(*cp);
		} while (*++cp);
		c = rachar;
		cerr = raerr;
	}
	/*
	 * terminate partial line with a hidden newline
	 */
	if (fold && *(cp - 1) != '\n')
		(void)printf(eflags & VIS_MIMESTYLE ? "=\n" : "\\\n");
}
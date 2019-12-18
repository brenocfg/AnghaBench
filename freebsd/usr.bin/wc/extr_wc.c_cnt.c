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
typedef  scalar_t__ uintmax_t ;
typedef  char u_char ;
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  mbs ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int MAXBSIZE ; 
 int MB_CUR_MAX ; 
 int STDIN_FILENO ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ dochar ; 
 scalar_t__ doline ; 
 scalar_t__ dolongline ; 
 scalar_t__ domulti ; 
 scalar_t__ doword ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fa ; 
 int fileargs_open (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ iswspace (int) ; 
 size_t mbrtowc (int*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  reset_siginfo () ; 
 int /*<<< orphan*/  show_cnt (char const*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ siginfo ; 
 int /*<<< orphan*/  tcharct ; 
 int /*<<< orphan*/  tlinect ; 
 scalar_t__ tlongline ; 
 int /*<<< orphan*/  twordct ; 
 int /*<<< orphan*/  xo_warn (char*,char const*) ; 

__attribute__((used)) static int
cnt(const char *file)
{
	struct stat sb;
	uintmax_t linect, wordct, charct, llct, tmpll;
	int fd, len, warned;
	size_t clen;
	short gotsp;
	u_char *p;
	u_char buf[MAXBSIZE];
	wchar_t wch;
	mbstate_t mbs;

	linect = wordct = charct = llct = tmpll = 0;
	if (file == NULL)
		fd = STDIN_FILENO;
	else if ((fd = fileargs_open(fa, file)) < 0) {
		xo_warn("%s: open", file);
		return (1);
	}
	if (doword || (domulti && MB_CUR_MAX != 1))
		goto word;
	/*
	 * If all we need is the number of characters and it's a regular file,
	 * just stat it.
	 */
	if (doline == 0 && dolongline == 0) {
		if (fstat(fd, &sb)) {
			xo_warn("%s: fstat", file);
			(void)close(fd);
			return (1);
		}
		if (S_ISREG(sb.st_mode)) {
			reset_siginfo();
			charct = sb.st_size;
			show_cnt(file, linect, wordct, charct, llct);
			tcharct += charct;
			(void)close(fd);
			return (0);
		}
	}
	/*
	 * For files we can't stat, or if we need line counting, slurp the
	 * file.  Line counting is split out because it's a lot faster to get
	 * lines than to get words, since the word count requires locale
	 * handling.
	 */
	while ((len = read(fd, buf, MAXBSIZE))) {
		if (len == -1) {
			xo_warn("%s: read", file);
			(void)close(fd);
			return (1);
		}
		if (siginfo)
			show_cnt(file, linect, wordct, charct, llct);
		charct += len;
		if (doline || dolongline) {
			for (p = buf; len--; ++p)
				if (*p == '\n') {
					if (tmpll > llct)
						llct = tmpll;
					tmpll = 0;
					++linect;
				} else
					tmpll++;
		}
	}
	reset_siginfo();
	if (doline)
		tlinect += linect;
	if (dochar)
		tcharct += charct;
	if (dolongline && llct > tlongline)
		tlongline = llct;
	show_cnt(file, linect, wordct, charct, llct);
	(void)close(fd);
	return (0);

	/* Do it the hard way... */
word:	gotsp = 1;
	warned = 0;
	memset(&mbs, 0, sizeof(mbs));
	while ((len = read(fd, buf, MAXBSIZE)) != 0) {
		if (len == -1) {
			xo_warn("%s: read", file != NULL ? file : "stdin");
			(void)close(fd);
			return (1);
		}
		p = buf;
		while (len > 0) {
			if (siginfo)
				show_cnt(file, linect, wordct, charct, llct);
			if (!domulti || MB_CUR_MAX == 1) {
				clen = 1;
				wch = (unsigned char)*p;
			} else if ((clen = mbrtowc(&wch, p, len, &mbs)) ==
			    (size_t)-1) {
				if (!warned) {
					errno = EILSEQ;
					xo_warn("%s",
					    file != NULL ? file : "stdin");
					warned = 1;
				}
				memset(&mbs, 0, sizeof(mbs));
				clen = 1;
				wch = (unsigned char)*p;
			} else if (clen == (size_t)-2)
				break;
			else if (clen == 0)
				clen = 1;
			charct++;
			if (wch != L'\n')
				tmpll++;
			len -= clen;
			p += clen;
			if (wch == L'\n') {
				if (tmpll > llct)
					llct = tmpll;
				tmpll = 0;
				++linect;
			}
			if (iswspace(wch))
				gotsp = 1;
			else if (gotsp) {
				gotsp = 0;
				++wordct;
			}
		}
	}
	reset_siginfo();
	if (domulti && MB_CUR_MAX > 1)
		if (mbrtowc(NULL, NULL, 0, &mbs) == (size_t)-1 && !warned)
			xo_warn("%s", file != NULL ? file : "stdin");
	if (doline)
		tlinect += linect;
	if (doword)
		twordct += wordct;
	if (dochar || domulti)
		tcharct += charct;
	if (dolongline && llct > tlongline)
		tlongline = llct;
	show_cnt(file, linect, wordct, charct, llct);
	(void)close(fd);
	return (0);
}
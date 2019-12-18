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
typedef  char wchar_t ;
struct winsize {int ws_col; } ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  mbs ;

/* Variables and functions */
 scalar_t__ EIO ; 
 int EOF ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int atoi (char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  fputc (char,scalar_t__) ; 
 int /*<<< orphan*/  fwrite (char*,int,size_t,scalar_t__) ; 
 char* getenv (char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 scalar_t__ iswprint (char) ; 
 size_t mbrtowc (char*,char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ outfile ; 
 int /*<<< orphan*/  outfname ; 
 scalar_t__ stdout ; 
 char* strchr (char const*,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int wctob (char) ; 
 int wcwidth (char) ; 

__attribute__((used)) static void
lputs(char *s, size_t len)
{
	static const char escapes[] = "\\\a\b\f\r\t\v";
	int c, col, width;
	const char *p;
	struct winsize win;
	static int termwidth = -1;
	size_t clen, i;
	wchar_t wc;
	mbstate_t mbs;

	if (outfile != stdout)
		termwidth = 60;
	if (termwidth == -1) {
		if ((p = getenv("COLUMNS")) && *p != '\0')
			termwidth = atoi(p);
		else if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &win) == 0 &&
		    win.ws_col > 0)
			termwidth = win.ws_col;
		else
			termwidth = 60;
	}
	if (termwidth <= 0)
		termwidth = 1;

	memset(&mbs, 0, sizeof(mbs));
	col = 0;
	while (len != 0) {
		clen = mbrtowc(&wc, s, len, &mbs);
		if (clen == 0)
			clen = 1;
		if (clen == (size_t)-1 || clen == (size_t)-2) {
			wc = (unsigned char)*s;
			clen = 1;
			memset(&mbs, 0, sizeof(mbs));
		}
		if (wc == '\n') {
			if (col + 1 >= termwidth)
				fprintf(outfile, "\\\n");
			fputc('$', outfile);
			fputc('\n', outfile);
			col = 0;
		} else if (iswprint(wc)) {
			width = wcwidth(wc);
			if (col + width >= termwidth) {
				fprintf(outfile, "\\\n");
				col = 0;
			}
			fwrite(s, 1, clen, outfile);
			col += width;
		} else if (wc != L'\0' && (c = wctob(wc)) != EOF &&
		    (p = strchr(escapes, c)) != NULL) {
			if (col + 2 >= termwidth) {
				fprintf(outfile, "\\\n");
				col = 0;
			}
			fprintf(outfile, "\\%c", "\\abfrtv"[p - escapes]);
			col += 2;
		} else {
			if (col + 4 * clen >= (unsigned)termwidth) {
				fprintf(outfile, "\\\n");
				col = 0;
			}
			for (i = 0; i < clen; i++)
				fprintf(outfile, "\\%03o",
				    (int)(unsigned char)s[i]);
			col += 4 * clen;
		}
		s += clen;
		len -= clen;
	}
	if (col + 1 >= termwidth)
		fprintf(outfile, "\\\n");
	(void)fputc('$', outfile);
	(void)fputc('\n', outfile);
	if (ferror(outfile))
		errx(1, "%s: %s", outfname, strerror(errno ? errno : EIO));
}
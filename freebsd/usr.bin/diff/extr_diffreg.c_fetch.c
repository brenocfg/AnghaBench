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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ D_CONTEXT ; 
 scalar_t__ D_EDIT ; 
 int D_EXPANDTABS ; 
 scalar_t__ D_GFORMAT ; 
 scalar_t__ D_IFDEF ; 
 scalar_t__ D_NORMAL ; 
 scalar_t__ D_NREVERSE ; 
 scalar_t__ D_REVERSE ; 
 scalar_t__ D_UNIFIED ; 
 int EOF ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ Tflag ; 
 scalar_t__ diff_format ; 
 int /*<<< orphan*/  diff_output (char*,...) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int ifdefname ; 
 int inifdef ; 
 int tabsize ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
fetch(long *f, int a, int b, FILE *lb, int ch, int oldfile, int flags)
{
	int i, j, c, lastc, col, nc;
	int	newcol;

	/*
	 * When doing #ifdef's, copy down to current line
	 * if this is the first file, so that stuff makes it to output.
	 */
	if ((diff_format == D_IFDEF) && oldfile) {
		long curpos = ftell(lb);
		/* print through if append (a>b), else to (nb: 0 vs 1 orig) */
		nc = f[a > b ? b : a - 1] - curpos;
		for (i = 0; i < nc; i++)
			diff_output("%c", getc(lb));
	}
	if (a > b)
		return (0);
	if (diff_format == D_IFDEF) {
		if (inifdef) {
			diff_output("#else /* %s%s */\n",
			    oldfile == 1 ? "!" : "", ifdefname);
		} else {
			if (oldfile)
				diff_output("#ifndef %s\n", ifdefname);
			else
				diff_output("#ifdef %s\n", ifdefname);
		}
		inifdef = 1 + oldfile;
	}
	for (i = a; i <= b; i++) {
		fseek(lb, f[i - 1], SEEK_SET);
		nc = f[i] - f[i - 1];
		if ((diff_format != D_IFDEF && diff_format != D_GFORMAT) &&
		    ch != '\0') {
			diff_output("%c", ch);
			if (Tflag && (diff_format == D_NORMAL || diff_format == D_CONTEXT
			    || diff_format == D_UNIFIED))
				diff_output("\t");
			else if (diff_format != D_UNIFIED)
				diff_output(" ");
		}
		col = 0;
		for (j = 0, lastc = '\0'; j < nc; j++, lastc = c) {
			if ((c = getc(lb)) == EOF) {
				if (diff_format == D_EDIT || diff_format == D_REVERSE ||
				    diff_format == D_NREVERSE)
					warnx("No newline at end of file");
				else
					diff_output("\n\\ No newline at end of "
					    "file\n");
				return (0);
			}
			if (c == '\t' && (flags & D_EXPANDTABS)) {
				newcol = ((col/tabsize)+1)*tabsize;
				do {
					diff_output(" ");
				} while (++col < newcol);
			} else {
				if (diff_format == D_EDIT && j == 1 && c == '\n'
				    && lastc == '.') {
					/*
					 * Don't print a bare "." line
					 * since that will confuse ed(1).
					 * Print ".." instead and return,
					 * giving the caller an offset
					 * from which to restart.
					 */
					diff_output(".\n");
					return (i - a + 1);
				}
				diff_output("%c", c);
				col++;
			}
		}
	}
	return (0);
}
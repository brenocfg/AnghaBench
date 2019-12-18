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
struct stat {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  enum STYLE { ____Placeholder_STYLE } STYLE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
#define  FBYTES 131 
#define  FLINES 130 
#define  RBYTES 129 
#define  RLINES 128 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytes (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ierr (char const*) ; 
 int /*<<< orphan*/  lines (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oerr () ; 
 int putchar (int) ; 
 int /*<<< orphan*/  rlines (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  stdout ; 

void
forward(FILE *fp, const char *fn, enum STYLE style, off_t off, struct stat *sbp)
{
	int ch;

	switch(style) {
	case FBYTES:
		if (off == 0)
			break;
		if (S_ISREG(sbp->st_mode)) {
			if (sbp->st_size < off)
				off = sbp->st_size;
			if (fseeko(fp, off, SEEK_SET) == -1) {
				ierr(fn);
				return;
			}
		} else while (off--)
			if ((ch = getc(fp)) == EOF) {
				if (ferror(fp)) {
					ierr(fn);
					return;
				}
				break;
			}
		break;
	case FLINES:
		if (off == 0)
			break;
		for (;;) {
			if ((ch = getc(fp)) == EOF) {
				if (ferror(fp)) {
					ierr(fn);
					return;
				}
				break;
			}
			if (ch == '\n' && !--off)
				break;
		}
		break;
	case RBYTES:
		if (S_ISREG(sbp->st_mode)) {
			if (sbp->st_size >= off &&
			    fseeko(fp, -off, SEEK_END) == -1) {
				ierr(fn);
				return;
			}
		} else if (off == 0) {
			while (getc(fp) != EOF);
			if (ferror(fp)) {
				ierr(fn);
				return;
			}
		} else
			if (bytes(fp, fn, off))
				return;
		break;
	case RLINES:
		if (S_ISREG(sbp->st_mode))
			if (!off) {
				if (fseeko(fp, (off_t)0, SEEK_END) == -1) {
					ierr(fn);
					return;
				}
			} else
				rlines(fp, fn, off, sbp);
		else if (off == 0) {
			while (getc(fp) != EOF);
			if (ferror(fp)) {
				ierr(fn);
				return;
			}
		} else
			if (lines(fp, fn, off))
				return;
		break;
	default:
		break;
	}

	while ((ch = getc(fp)) != EOF)
		if (putchar(ch) == EOF)
			oerr();
	if (ferror(fp)) {
		ierr(fn);
		return;
	}
	(void)fflush(stdout);
}
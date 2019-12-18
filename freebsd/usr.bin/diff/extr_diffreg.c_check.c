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
 int D_FOLDBLANKS ; 
 int D_IGNOREBLANKS ; 
 int D_IGNORECASE ; 
 int D_STRIPCR ; 
 int EOF ; 
 int* J ; 
 scalar_t__ chrtran (int) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (int) ; 
 long* ixnew ; 
 long* ixold ; 
 int* len ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 void* skipline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
check(FILE *f1, FILE *f2, int flags)
{
	int i, j, jackpot, c, d;
	long ctold, ctnew;

	rewind(f1);
	rewind(f2);
	j = 1;
	ixold[0] = ixnew[0] = 0;
	jackpot = 0;
	ctold = ctnew = 0;
	for (i = 1; i <= len[0]; i++) {
		if (J[i] == 0) {
			ixold[i] = ctold += skipline(f1);
			continue;
		}
		while (j < J[i]) {
			ixnew[j] = ctnew += skipline(f2);
			j++;
		}
		if (flags & (D_FOLDBLANKS|D_IGNOREBLANKS|D_IGNORECASE|D_STRIPCR)) {
			for (;;) {
				c = getc(f1);
				d = getc(f2);
				/*
				 * GNU diff ignores a missing newline
				 * in one file for -b or -w.
				 */
				if (flags & (D_FOLDBLANKS|D_IGNOREBLANKS)) {
					if (c == EOF && d == '\n') {
						ctnew++;
						break;
					} else if (c == '\n' && d == EOF) {
						ctold++;
						break;
					}
				}
				ctold++;
				ctnew++;
				if (flags & D_STRIPCR && (c == '\r' || d == '\r')) {
					if (c == '\r') {
						if ((c = getc(f1)) == '\n') {
							ctold++;
						} else {
							ungetc(c, f1);
						}
					}
					if (d == '\r') {
						if ((d = getc(f2)) == '\n') {
							ctnew++;
						} else {
							ungetc(d, f2);
						}
					}
					break;
				}
				if ((flags & D_FOLDBLANKS) && isspace(c) &&
				    isspace(d)) {
					do {
						if (c == '\n')
							break;
						ctold++;
					} while (isspace(c = getc(f1)));
					do {
						if (d == '\n')
							break;
						ctnew++;
					} while (isspace(d = getc(f2)));
				} else if ((flags & D_IGNOREBLANKS)) {
					while (isspace(c) && c != '\n') {
						c = getc(f1);
						ctold++;
					}
					while (isspace(d) && d != '\n') {
						d = getc(f2);
						ctnew++;
					}
				}
				if (chrtran(c) != chrtran(d)) {
					jackpot++;
					J[i] = 0;
					if (c != '\n' && c != EOF)
						ctold += skipline(f1);
					if (d != '\n' && c != EOF)
						ctnew += skipline(f2);
					break;
				}
				if (c == '\n' || c == EOF)
					break;
			}
		} else {
			for (;;) {
				ctold++;
				ctnew++;
				if ((c = getc(f1)) != (d = getc(f2))) {
					/* jackpot++; */
					J[i] = 0;
					if (c != '\n' && c != EOF)
						ctold += skipline(f1);
					if (d != '\n' && c != EOF)
						ctnew += skipline(f2);
					break;
				}
				if (c == '\n' || c == EOF)
					break;
			}
		}
		ixold[i] = ctold;
		ixnew[j] = ctnew;
		j++;
	}
	for (; j <= len[1]; j++) {
		ixnew[j] = ctnew += skipline(f2);
	}
	/*
	 * if (jackpot)
	 *	fprintf(stderr, "jackpot\n");
	 */
}
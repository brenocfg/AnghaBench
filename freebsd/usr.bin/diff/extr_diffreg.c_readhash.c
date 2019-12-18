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
#define  EOF 128 
 int chrtran (int) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
readhash(FILE *f, int flags)
{
	int i, t, space;
	int sum;

	sum = 1;
	space = 0;
	if ((flags & (D_FOLDBLANKS|D_IGNOREBLANKS)) == 0) {
		if (flags & D_IGNORECASE)
			for (i = 0; (t = getc(f)) != '\n'; i++) {
				if (flags & D_STRIPCR && t == '\r') {
					t = getc(f);
					if (t == '\n')
						break;
					ungetc(t, f);
				}
				if (t == EOF) {
					if (i == 0)
						return (0);
					break;
				}
				sum = sum * 127 + chrtran(t);
			}
		else
			for (i = 0; (t = getc(f)) != '\n'; i++) {
				if (flags & D_STRIPCR && t == '\r') {
					t = getc(f);
					if (t == '\n')
						break;
					ungetc(t, f);
				}
				if (t == EOF) {
					if (i == 0)
						return (0);
					break;
				}
				sum = sum * 127 + t;
			}
	} else {
		for (i = 0;;) {
			switch (t = getc(f)) {
			case '\r':
			case '\t':
			case '\v':
			case '\f':
			case ' ':
				space++;
				continue;
			default:
				if (space && (flags & D_IGNOREBLANKS) == 0) {
					i++;
					space = 0;
				}
				sum = sum * 127 + chrtran(t);
				i++;
				continue;
			case EOF:
				if (i == 0)
					return (0);
				/* FALLTHROUGH */
			case '\n':
				break;
			}
			break;
		}
	}
	/*
	 * There is a remote possibility that we end up with a zero sum.
	 * Zero is used as an EOF marker, so return 1 instead.
	 */
	return (sum == 0 ? 1 : sum);
}
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
 int EOF ; 
 int /*<<< orphan*/  MOVEC (char) ; 
 int /*<<< orphan*/  TESTD (int) ; 
 int /*<<< orphan*/  TESTP ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
parse(FILE *fp)
{
	int ch, s1, s2, s3;

#define	TESTD(s) {							\
	if ((s = getc(fp)) == EOF)					\
		return;							\
	if (!isdigit(s))						\
		continue;						\
}
#define	TESTP {								\
	if ((ch = getc(fp)) == EOF)					\
		return;							\
	if (ch != '|')							\
		continue;						\
}
#define	MOVEC(t) {							\
	do {								\
		if ((ch = getc(fp)) == EOF)				\
			return;						\
	} while (ch != (t));						\
}
	for (;;) {
		MOVEC('"');
		TESTD(s1);
		TESTD(s2);
		TESTD(s3);
		TESTP;
		putchar('"');
		putchar(s1);
		putchar(s2);
		putchar(s3);
		putchar('|');
		for (;;) {		/* dump to end quote. */
			if ((ch = getc(fp)) == EOF)
				return;
			putchar(ch);
			if (ch == '"')
				break;
			if (ch == '\\') {
				if ((ch = getc(fp)) == EOF)
					return;
				putchar(ch);
			}
		}
		putchar('\n');
	}
}
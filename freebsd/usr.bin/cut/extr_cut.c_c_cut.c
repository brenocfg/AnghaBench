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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char WEOF ; 
 scalar_t__ autostop ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 char getwc (int /*<<< orphan*/ *) ; 
 int maxval ; 
 char* positions ; 
 int /*<<< orphan*/  putwchar (char) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static int
c_cut(FILE *fp, const char *fname)
{
	wint_t ch;
	int col;
	char *pos;

	ch = 0;
	for (;;) {
		pos = positions + 1;
		for (col = maxval; col; --col) {
			if ((ch = getwc(fp)) == WEOF)
				goto out;
			if (ch == '\n')
				break;
			if (*pos++)
				(void)putwchar(ch);
		}
		if (ch != '\n') {
			if (autostop)
				while ((ch = getwc(fp)) != WEOF && ch != '\n')
					(void)putwchar(ch);
			else
				while ((ch = getwc(fp)) != WEOF && ch != '\n');
		}
		(void)putwchar('\n');
	}
out:
	if (ferror(fp)) {
		warn("%s", fname);
		return (1);
	}
	return (0);
}
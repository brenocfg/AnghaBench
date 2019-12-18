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

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getchar () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * koi2alt ; 
 scalar_t__ length ; 
 scalar_t__ lines ; 
 int /*<<< orphan*/  putchar (int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	int c, i;
	char *cp;

	while (--argc) {
		if (*(cp = *++argv) == '-') {
			switch (*++cp) {
			case 'l':
				if ((i = atoi(++cp)) > 0)
					length = i;
				break;
			}
		}
	}

	while ((c = getchar()) != EOF) {
		if (c == '\031') {
			if ((c = getchar()) == '\1') {
				lines = 0;
				fflush(stdout);
				kill(getpid(), SIGSTOP);
				continue;
			} else {
				ungetc(c, stdin);
				c = '\031';
			}
		} else if (c & 0x80) {
			fputs(koi2alt[c & 0x7F], stdout);
			continue;
		} else if (c == '\n')
			lines++;
		else if (c == '\f')
			lines = length;
		putchar(c);
		if (lines >= length) {
			lines = 0;
			fflush(stdout);
		}
	}
	return 0;
}
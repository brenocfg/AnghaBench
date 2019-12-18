#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char wint_t ;
typedef  char wchar_t ;
struct TYPE_3__ {int cnt; char* name; int /*<<< orphan*/ * fp; struct TYPE_3__* next; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 char WEOF ; 
 char* delim ; 
 int delimcnt ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char getwc (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  putwchar (char) ; 
 int /*<<< orphan*/ * stdin ; 

__attribute__((used)) static int
parallel(char **argv)
{
	LIST *lp;
	int cnt;
	wint_t ich;
	wchar_t ch;
	char *p;
	LIST *head, *tmp;
	int opencnt, output;

	for (cnt = 0, head = tmp = NULL; (p = *argv); ++argv, ++cnt) {
		if ((lp = malloc(sizeof(LIST))) == NULL)
			err(1, NULL);
		if (p[0] == '-' && !p[1])
			lp->fp = stdin;
		else if (!(lp->fp = fopen(p, "r")))
			err(1, "%s", p);
		lp->next = NULL;
		lp->cnt = cnt;
		lp->name = p;
		if (!head)
			head = tmp = lp;
		else {
			tmp->next = lp;
			tmp = lp;
		}
	}

	for (opencnt = cnt; opencnt;) {
		for (output = 0, lp = head; lp; lp = lp->next) {
			if (!lp->fp) {
				if (output && lp->cnt &&
				    (ch = delim[(lp->cnt - 1) % delimcnt]))
					putwchar(ch);
				continue;
			}
			if ((ich = getwc(lp->fp)) == WEOF) {
				if (!--opencnt)
					break;
				lp->fp = NULL;
				if (output && lp->cnt &&
				    (ch = delim[(lp->cnt - 1) % delimcnt]))
					putwchar(ch);
				continue;
			}
			/*
			 * make sure that we don't print any delimiters
			 * unless there's a non-empty file.
			 */
			if (!output) {
				output = 1;
				for (cnt = 0; cnt < lp->cnt; ++cnt)
					if ((ch = delim[cnt % delimcnt]))
						putwchar(ch);
			} else if ((ch = delim[(lp->cnt - 1) % delimcnt]))
				putwchar(ch);
			if (ich == '\n')
				continue;
			do {
				putwchar(ich);
			} while ((ich = getwc(lp->fp)) != WEOF && ich != '\n');
		}
		if (output)
			putwchar('\n');
	}

	return (0);
}
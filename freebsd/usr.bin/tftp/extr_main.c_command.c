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
struct cmd {int /*<<< orphan*/  (* handler ) (scalar_t__,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  History ;
typedef  int /*<<< orphan*/  HistEvent ;
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 int /*<<< orphan*/  H_ENTER ; 
 int MAXLINE ; 
 int MIN (int,int) ; 
 char* el_gets (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 struct cmd* getcmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  makeargv (char*) ; 
 scalar_t__ margc ; 
 int /*<<< orphan*/ * margv ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdin ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txrx_error ; 

__attribute__((used)) static void
command(bool interactive, EditLine *el, History *hist, HistEvent *hep)
{
	struct cmd *c;
	const char *bp;
	char *cp;
	int len, num;
	char	line[MAXLINE];

	for (;;) {
		if (interactive) {
			if ((bp = el_gets(el, &num)) == NULL || num == 0)
				exit(0);
			len = MIN(MAXLINE, num);
			memcpy(line, bp, len);
			line[len - 1] = '\0';
			history(hist, hep, H_ENTER, bp);
		} else {
			line[0] = 0;
			if (fgets(line, sizeof line , stdin) == NULL) {
				if (feof(stdin)) {
					exit(txrx_error);
				} else {
					continue;
				}
			}
		}
		if ((cp = strchr(line, '\n')))
			*cp = '\0';
		if (line[0] == 0)
			continue;
		makeargv(line);
		if (margc == 0)
			continue;
		c = getcmd(margv[0]);
		if (c == (struct cmd *)-1) {
			printf("?Ambiguous command\n");
			continue;
		}
		if (c == NULL) {
			printf("?Invalid command\n");
			continue;
		}
		(*c->handler)(margc, margv);
	}
}
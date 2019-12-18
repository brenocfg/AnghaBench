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
typedef  size_t u_int ;
struct winsize {size_t ws_col; } ;

/* Variables and functions */
 size_t MAXIMUM (size_t,int) ; 
 size_t MINIMUM (size_t,size_t) ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 int /*<<< orphan*/  mprintf (char*,size_t,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int strlen (char*) ; 

__attribute__((used)) static void
complete_display(char **list, u_int len)
{
	u_int y, m = 0, width = 80, columns = 1, colspace = 0, llen;
	struct winsize ws;
	char *tmp;

	/* Count entries for sort and find longest */
	for (y = 0; list[y]; y++)
		m = MAXIMUM(m, strlen(list[y]));

	if (ioctl(fileno(stdin), TIOCGWINSZ, &ws) != -1)
		width = ws.ws_col;

	m = m > len ? m - len : 0;
	columns = width / (m + 2);
	columns = MAXIMUM(columns, 1);
	colspace = width / columns;
	colspace = MINIMUM(colspace, width);

	printf("\n");
	m = 1;
	for (y = 0; list[y]; y++) {
		llen = strlen(list[y]);
		tmp = llen > len ? list[y] + len : "";
		mprintf("%-*s", colspace, tmp);
		if (m >= columns) {
			printf("\n");
			m = 1;
		} else
			m++;
	}
	printf("\n");
}
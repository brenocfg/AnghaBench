#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double ksw_total; double ksw_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT (double) ; 
 int /*<<< orphan*/  cur_dev ; 
 scalar_t__ dlen ; 
 int /*<<< orphan*/  dsshow (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hlen ; 
 TYPE_1__* kvmsw ; 
 int kvnsw ; 
 int /*<<< orphan*/  labelswap () ; 
 int /*<<< orphan*/  last_dev ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 scalar_t__ odlen ; 
 int okvnsw ; 
 scalar_t__ oulen ; 
 scalar_t__ ulen ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  wnd ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 

void
showswap(void)
{
	int count;
	int i;

	if (kvnsw != okvnsw || dlen != odlen || ulen != oulen)
		labelswap();

	for (i = 0; i <= kvnsw; ++i) {
		if (i == kvnsw) {
			if (kvnsw == 1)
				break;
		}

		if (kvmsw[i].ksw_total == 0) {
			mvwprintw(
			    wnd,
			    i + 1,
			    dlen + hlen + ulen + 1,
			    "(swap not configured)"
			);
			continue;
		}

		wmove(wnd, i + 1, dlen);

		wprintw(wnd, "%*d", hlen, CONVERT(kvmsw[i].ksw_total));
		wprintw(wnd, "%*d", ulen, CONVERT(kvmsw[i].ksw_used));

		count = 50.0 * kvmsw[i].ksw_used / kvmsw[i].ksw_total + 1;

		waddch(wnd, ' ');
		while (count--)
			waddch(wnd, 'X');
		wclrtoeol(wnd);
	}
	dsshow(12, 0, 18, &cur_dev, &last_dev);
}
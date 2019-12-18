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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int MIN (int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,long double) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnd ; 

__attribute__((used)) static void
histogram(long double val, int colwidth, double scale)
{
	char buf[10];
	int k;
	int v = (int)(val * scale) + 0.5;

	k = MIN(v, colwidth);
	if (v > colwidth) {
		snprintf(buf, sizeof(buf), "%5.2Lf", val);
		k -= strlen(buf);
		while (k--)
			waddch(wnd, 'X');
		waddstr(wnd, buf);
		return;
	}
	while (k--)
		waddch(wnd, 'X');
	wclrtoeol(wnd);
}
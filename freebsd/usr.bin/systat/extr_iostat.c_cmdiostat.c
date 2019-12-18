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
 int /*<<< orphan*/  cur_dev ; 
 int /*<<< orphan*/  dscmd (char const*,char const*,int,int /*<<< orphan*/ *) ; 
 int kbpt ; 
 int /*<<< orphan*/  labeliostat () ; 
 int numbers ; 
 scalar_t__ prefix (char const*,char*) ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  wclear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnd ; 

int
cmdiostat(const char *cmd, const char *args)
{

	if (prefix(cmd, "kbpt"))
		kbpt = !kbpt;
	else if (prefix(cmd, "numbers"))
		numbers = 1;
	else if (prefix(cmd, "bars"))
		numbers = 0;
	else if (!dscmd(cmd, args, 100, &cur_dev))
		return (0);
	wclear(wnd);
	labeliostat();
	refresh();
	return (1);
}
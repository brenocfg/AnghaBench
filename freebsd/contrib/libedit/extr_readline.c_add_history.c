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
struct TYPE_3__ {scalar_t__ num; } ;
typedef  TYPE_1__ HistEvent ;

/* Variables and functions */
 int /*<<< orphan*/  H_ENTER ; 
 int /*<<< orphan*/  H_GETSIZE ; 
 int /*<<< orphan*/ * e ; 
 int /*<<< orphan*/ * h ; 
 int history (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  history_base ; 
 scalar_t__ history_length ; 
 int /*<<< orphan*/  history_offset ; 
 int /*<<< orphan*/  rl_initialize () ; 

int
add_history(const char *line)
{
	HistEvent ev;

	if (h == NULL || e == NULL)
		rl_initialize();

	if (history(h, &ev, H_ENTER, line) == -1)
		return 0;

	(void)history(h, &ev, H_GETSIZE);
	if (ev.num == history_length)
		history_base++;
	else {
		history_offset++;
		history_length = ev.num;
	}
	return 0;
}
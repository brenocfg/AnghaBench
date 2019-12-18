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
 int EINVAL ; 
 int /*<<< orphan*/  H_GETSIZE ; 
 int /*<<< orphan*/  H_LOAD ; 
 char* _default_history_file () ; 
 int /*<<< orphan*/ * e ; 
 int errno ; 
 int /*<<< orphan*/ * h ; 
 int history (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ history_length ; 
 int /*<<< orphan*/  rl_initialize () ; 

int
read_history(const char *filename)
{
	HistEvent ev;

	if (h == NULL || e == NULL)
		rl_initialize();
	if (filename == NULL && (filename = _default_history_file()) == NULL)
		return errno;
	errno = 0;
	if (history(h, &ev, H_LOAD, filename) == -1)
	    return errno ? errno : EINVAL;
	if (history(h, &ev, H_GETSIZE) == 0)
		history_length = ev.num;
	if (history_length < 0)
		return EINVAL;
	return 0;
}
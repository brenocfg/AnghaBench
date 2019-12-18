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
typedef  int /*<<< orphan*/  HistEvent ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  H_SAVE ; 
 char* _default_history_file () ; 
 int /*<<< orphan*/ * e ; 
 int errno ; 
 int /*<<< orphan*/ * h ; 
 int history (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  rl_initialize () ; 

int
write_history(const char *filename)
{
	HistEvent ev;

	if (h == NULL || e == NULL)
		rl_initialize();
	if (filename == NULL && (filename = _default_history_file()) == NULL)
		return errno;
	return history(h, &ev, H_SAVE, filename) == -1 ?
	    (errno ? errno : EINVAL) : 0;
}
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
 int /*<<< orphan*/  H_SETSIZE ; 
 int INT_MAX ; 
 int /*<<< orphan*/  h ; 
 int /*<<< orphan*/  history (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int max_input_history ; 

int
unstifle_history(void)
{
	HistEvent ev;
	int omax;

	history(h, &ev, H_SETSIZE, INT_MAX);
	omax = max_input_history;
	max_input_history = INT_MAX;
	return omax;		/* some value _must_ be returned */
}
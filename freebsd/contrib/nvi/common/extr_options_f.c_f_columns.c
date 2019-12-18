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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  OPTION ;

/* Variables and functions */
 scalar_t__ MAXIMUM_SCREEN_COLS ; 
 scalar_t__ MINIMUM_SCREEN_COLS ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 

int
f_columns(
	SCR *sp,
	OPTION *op,
	char *str,
	u_long *valp)
{
	/* Validate the number. */
	if (*valp < MINIMUM_SCREEN_COLS) {
		msgq(sp, M_ERR, "040|Screen columns too small, less than %d",
		    MINIMUM_SCREEN_COLS);
		return (1);
	}

	/*
	 * !!!
	 * It's not uncommon for allocation of huge chunks of memory to cause
	 * core dumps on various systems.  So, we prune out numbers that are
	 * "obviously" wrong.  Vi will not work correctly if it has the wrong
	 * number of lines/columns for the screen, but at least we don't drop
	 * core.
	 */
#define	MAXIMUM_SCREEN_COLS	500
	if (*valp > MAXIMUM_SCREEN_COLS) {
		msgq(sp, M_ERR, "041|Screen columns too large, greater than %d",
		    MAXIMUM_SCREEN_COLS);
		return (1);
	}
	return (0);
}
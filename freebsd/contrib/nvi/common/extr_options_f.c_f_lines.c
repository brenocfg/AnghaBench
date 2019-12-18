#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_7__ {int defscroll; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  OPTION ;

/* Variables and functions */
 int MAXIMUM_SCREEN_ROWS ; 
 int MINIMUM_SCREEN_ROWS ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  OS_DEF ; 
 int O_D_VAL (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_LINES ; 
 int O_VAL (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_WINDOW ; 
 int /*<<< orphan*/  msgq (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  o_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
f_lines(
	SCR *sp,
	OPTION *op,
	char *str,
	u_long *valp)
{
	/* Validate the number. */
	if (*valp < MINIMUM_SCREEN_ROWS) {
		msgq(sp, M_ERR, "042|Screen lines too small, less than %d",
		    MINIMUM_SCREEN_ROWS);
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
#define	MAXIMUM_SCREEN_ROWS	500
	if (*valp > MAXIMUM_SCREEN_ROWS) {
		msgq(sp, M_ERR, "043|Screen lines too large, greater than %d",
		    MAXIMUM_SCREEN_ROWS);
		return (1);
	}

	/*
	 * Set the value, and the related scroll value.  If no window
	 * value set, set a new default window.
	 */
	o_set(sp, O_LINES, 0, NULL, *valp);
	if (*valp == 1) {
		sp->defscroll = 1;

		if (O_VAL(sp, O_WINDOW) == O_D_VAL(sp, O_WINDOW) ||
		    O_VAL(sp, O_WINDOW) > *valp) {
			o_set(sp, O_WINDOW, 0, NULL, 1);
			o_set(sp, O_WINDOW, OS_DEF, NULL, 1);
		}
	} else {
		sp->defscroll = (*valp - 1) / 2;

		if (O_VAL(sp, O_WINDOW) == O_D_VAL(sp, O_WINDOW) ||
		    O_VAL(sp, O_WINDOW) > *valp) {
			o_set(sp, O_WINDOW, 0, NULL, *valp - 1);
			o_set(sp, O_WINDOW, OS_DEF, NULL, *valp - 1);
		}
	}
	return (0);
}
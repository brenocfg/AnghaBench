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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_3__ {int cno; size_t ai; size_t offset; int /*<<< orphan*/ * lb; } ;
typedef  TYPE_1__ TEXT ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  EC_MAPINPUT ; 
 int /*<<< orphan*/  FL_CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FL_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ex_is_unmap (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ isblank (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
txt_unmap(SCR *sp, TEXT *tp, u_int32_t *ec_flagsp)
{
	size_t len, off;
	CHAR_T *p;

	/* Find the beginning of this "word". */
	for (off = tp->cno - 1, p = tp->lb + off, len = 0;; --p, --off) {
		if (isblank(*p)) {
			++p;
			break;
		}
		++len;
		if (off == tp->ai || off == tp->offset)
			break;
	}

	/*
	 * !!!
	 * Historic vi exploded input mappings on the command line.  See the
	 * txt_abbrev() routine for an explanation of the problems inherent
	 * in this.
	 *
	 * We make this work as follows.  If we get a string which is <blank>
	 * terminated and which starts at the beginning of the line, we check
	 * to see it is the unmap command.  If it is, we return that the input
	 * mapping should be turned off.  Note also, minor trickiness, so that
	 * if the user erases the line and starts another command, we go ahead
	 * an turn mapping back on.
	 */
	if ((off == tp->ai || off == tp->offset) && ex_is_unmap(p, len))
		FL_CLR(*ec_flagsp, EC_MAPINPUT);
	else
		FL_SET(*ec_flagsp, EC_MAPINPUT);
}
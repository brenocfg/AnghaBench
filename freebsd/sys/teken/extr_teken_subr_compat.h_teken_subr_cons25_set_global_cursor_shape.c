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
typedef  int /*<<< orphan*/  teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  TP_SETGLOBALCURSOR ; 
 int /*<<< orphan*/  teken_funcs_param (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
teken_subr_cons25_set_global_cursor_shape(const teken_t *t, unsigned int ncmds,
    const unsigned int cmds[])
{
	unsigned int code, i;

	/*
	 * Pack the args to work around API deficiencies.  This requires
	 * knowing too much about the low level to be fully compatible.
	 * Returning when ncmds > 3 is necessary and happens to be
	 * compatible.  Discarding high bits is necessary and happens to
	 * be incompatible only for invalid args when ncmds == 3.
	 */
	if (ncmds > 3)
		return;
	code = 0;
	for (i = ncmds; i > 0; i--)
		code = (code << 8) | (cmds[i - 1] & 0xff);
	code = (code << 8) | ncmds;
	teken_funcs_param(t, TP_SETGLOBALCURSOR, code);
}
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
typedef  int /*<<< orphan*/  xo_handle_t ;
typedef  int /*<<< orphan*/  uintmax_t ;

/* Variables and functions */
 scalar_t__ dochar ; 
 scalar_t__ doline ; 
 scalar_t__ dolongline ; 
 scalar_t__ domulti ; 
 scalar_t__ doword ; 
 scalar_t__ siginfo ; 
 int /*<<< orphan*/ * stderr_handle ; 
 int /*<<< orphan*/  xo_emit_h (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
show_cnt(const char *file, uintmax_t linect, uintmax_t wordct,
    uintmax_t charct, uintmax_t llct)
{
	xo_handle_t *xop;

	if (!siginfo)
		xop = NULL;
	else {
		xop = stderr_handle;
		siginfo = 0;
	}

	if (doline)
		xo_emit_h(xop, " {:lines/%7ju/%ju}", linect);
	if (doword)
		xo_emit_h(xop, " {:words/%7ju/%ju}", wordct);
	if (dochar || domulti)
		xo_emit_h(xop, " {:characters/%7ju/%ju}", charct);
	if (dolongline)
		xo_emit_h(xop, " {:long-lines/%7ju/%ju}", llct);
	if (file != NULL)
		xo_emit_h(xop, " {:filename/%s}\n", file);
	else
		xo_emit_h(xop, "\n");
}
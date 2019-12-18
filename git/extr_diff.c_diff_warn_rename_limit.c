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
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  degrade_cc_to_c_warning ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rename_limit_advice ; 
 int /*<<< orphan*/  rename_limit_warning ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,...) ; 

void diff_warn_rename_limit(const char *varname, int needed, int degraded_cc)
{
	fflush(stdout);
	if (degraded_cc)
		warning(_(degrade_cc_to_c_warning));
	else if (needed)
		warning(_(rename_limit_warning));
	else
		return;
	if (0 < needed)
		warning(_(rename_limit_advice), varname, needed);
}
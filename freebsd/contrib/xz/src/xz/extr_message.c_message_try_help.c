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
 int /*<<< orphan*/  V_WARNING ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  progname ; 

extern void
message_try_help(void)
{
	// Print this with V_WARNING instead of V_ERROR to prevent it from
	// showing up when --quiet has been specified.
	message(V_WARNING, _("Try `%s --help' for more information."),
			progname);
	return;
}
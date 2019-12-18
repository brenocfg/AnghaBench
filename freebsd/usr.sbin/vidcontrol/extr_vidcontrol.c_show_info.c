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
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  revert () ; 
 int /*<<< orphan*/  show_active_info () ; 
 int /*<<< orphan*/  show_adapter_info () ; 
 int /*<<< orphan*/  show_mode_info () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void
show_info(char *arg)
{

	if (!strcmp(arg, "active")) {
		show_active_info();
	} else if (!strcmp(arg, "adapter")) {
		show_adapter_info();
	} else if (!strcmp(arg, "mode")) {
		show_mode_info();
	} else {
		revert();
		errx(1, "argument to -i must be active, adapter, or mode");
	}
}
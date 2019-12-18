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
struct iter_hints {int dummy; } ;
struct config_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  hints_apply_cfg (struct iter_hints*,struct config_file*) ; 
 struct iter_hints* hints_create () ; 
 int /*<<< orphan*/  hints_delete (struct iter_hints*) ; 

__attribute__((used)) static void
check_hints(struct config_file* cfg)
{
	struct iter_hints* hints = hints_create();
	if(!hints || !hints_apply_cfg(hints, cfg)) {
		fatal_exit("Could not set root or stub hints");
	}
	hints_delete(hints);
}
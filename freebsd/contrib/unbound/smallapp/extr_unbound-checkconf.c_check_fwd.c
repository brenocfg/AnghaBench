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
struct iter_forwards {int dummy; } ;
struct config_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int /*<<< orphan*/  forwards_apply_cfg (struct iter_forwards*,struct config_file*) ; 
 struct iter_forwards* forwards_create () ; 
 int /*<<< orphan*/  forwards_delete (struct iter_forwards*) ; 

__attribute__((used)) static void
check_fwd(struct config_file* cfg)
{
	struct iter_forwards* fwd = forwards_create();
	if(!fwd || !forwards_apply_cfg(fwd, cfg)) {
		fatal_exit("Could not set forward zones");
	}
	forwards_delete(fwd);
}
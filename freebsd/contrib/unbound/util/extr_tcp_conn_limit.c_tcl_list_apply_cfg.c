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
struct tcl_list {int /*<<< orphan*/  tree; int /*<<< orphan*/  region; } ;
struct config_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  addr_tree_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addr_tree_init_parents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_tcl_list (struct tcl_list*,struct config_file*) ; 
 int /*<<< orphan*/  regional_free_all (int /*<<< orphan*/ ) ; 

int
tcl_list_apply_cfg(struct tcl_list* tcl, struct config_file* cfg)
{
	regional_free_all(tcl->region);
	addr_tree_init(&tcl->tree);
	if(!read_tcl_list(tcl, cfg))
		return 0;
	addr_tree_init_parents(&tcl->tree);
	return 1;
}
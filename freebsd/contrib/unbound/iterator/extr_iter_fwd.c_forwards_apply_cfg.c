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
struct iter_forwards {int /*<<< orphan*/  tree; } ;
struct config_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwd_cmp ; 
 int /*<<< orphan*/  fwd_del_tree (struct iter_forwards*) ; 
 int /*<<< orphan*/  fwd_init_parents (struct iter_forwards*) ; 
 int /*<<< orphan*/  make_stub_holes (struct iter_forwards*,struct config_file*) ; 
 int /*<<< orphan*/  rbtree_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_forwards (struct iter_forwards*,struct config_file*) ; 

int 
forwards_apply_cfg(struct iter_forwards* fwd, struct config_file* cfg)
{
	fwd_del_tree(fwd);
	fwd->tree = rbtree_create(fwd_cmp);
	if(!fwd->tree)
		return 0;

	/* read forward zones */
	if(!read_forwards(fwd, cfg))
		return 0;
	if(!make_stub_holes(fwd, cfg))
		return 0;
	fwd_init_parents(fwd);
	return 1;
}
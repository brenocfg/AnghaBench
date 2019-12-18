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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iter_forwards {int /*<<< orphan*/  tree; } ;
struct iter_forward_zone {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwd_init_parents (struct iter_forwards*) ; 
 struct iter_forward_zone* fwd_zone_find (struct iter_forwards*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwd_zone_free (struct iter_forward_zone*) ; 
 int /*<<< orphan*/  rbtree_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void 
forwards_delete_zone(struct iter_forwards* fwd, uint16_t c, uint8_t* nm)
{
	struct iter_forward_zone *z;
	if(!(z=fwd_zone_find(fwd, c, nm)))
		return; /* nothing to do */
	(void)rbtree_delete(fwd->tree, &z->node);
	fwd_zone_free(z);
	fwd_init_parents(fwd);
}
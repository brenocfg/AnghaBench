#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct TYPE_2__ {scalar_t__ strong; scalar_t__ weak; } ;
struct binder_ref {TYPE_1__ data; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int binder_inc_node (int /*<<< orphan*/ ,int,int,struct list_head*) ; 

__attribute__((used)) static int binder_inc_ref_olocked(struct binder_ref *ref, int strong,
				  struct list_head *target_list)
{
	int ret;

	if (strong) {
		if (ref->data.strong == 0) {
			ret = binder_inc_node(ref->node, 1, 1, target_list);
			if (ret)
				return ret;
		}
		ref->data.strong++;
	} else {
		if (ref->data.weak == 0) {
			ret = binder_inc_node(ref->node, 0, 1, target_list);
			if (ret)
				return ret;
		}
		ref->data.weak++;
	}
	return 0;
}
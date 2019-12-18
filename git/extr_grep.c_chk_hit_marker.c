#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct grep_expr* right; TYPE_1__* left; } ;
struct TYPE_6__ {TYPE_2__ binary; } ;
struct grep_expr {scalar_t__ node; int hit; TYPE_3__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  hit; } ;

/* Variables and functions */
 scalar_t__ GREP_NODE_OR ; 

__attribute__((used)) static int chk_hit_marker(struct grep_expr *x)
{
	/* Top level nodes have hit markers.  See if they all are hits */
	while (1) {
		if (x->node != GREP_NODE_OR)
			return x->hit;
		if (!x->u.binary.left->hit)
			return 0;
		x = x->u.binary.right;
	}
}
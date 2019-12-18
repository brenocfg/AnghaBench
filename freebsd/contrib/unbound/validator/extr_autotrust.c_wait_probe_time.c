#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct val_anchors {TYPE_1__* autr; } ;
struct trust_anchor {TYPE_2__* autr; } ;
struct TYPE_8__ {scalar_t__ key; } ;
typedef  TYPE_3__ rbnode_type ;
struct TYPE_7__ {int /*<<< orphan*/  next_probe_time; } ;
struct TYPE_6__ {int /*<<< orphan*/  probe; } ;

/* Variables and functions */
 TYPE_3__* RBTREE_NULL ; 
 TYPE_3__* rbtree_first (int /*<<< orphan*/ *) ; 

__attribute__((used)) static time_t
wait_probe_time(struct val_anchors* anchors)
{
	rbnode_type* t = rbtree_first(&anchors->autr->probe);
	if(t != RBTREE_NULL) 
		return ((struct trust_anchor*)t->key)->autr->next_probe_time;
	return 0;
}
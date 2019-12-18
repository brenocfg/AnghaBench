#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int (* cmp ) (void const*,void const*) ;scalar_t__ count; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ rbtree_type ;

/* Variables and functions */
 int /*<<< orphan*/  RBTREE_NULL ; 

void 
rbtree_init(rbtree_type *rbtree, int (*cmpf)(const void *, const void *))
{
	/* Initialize it */
	rbtree->root = RBTREE_NULL;
	rbtree->count = 0;
	rbtree->cmp = cmpf;
}
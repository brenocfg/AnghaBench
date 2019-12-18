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
typedef  TYPE_1__ ldns_rbtree_t ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RBTREE_NULL ; 

void 
ldns_rbtree_init(ldns_rbtree_t *rbtree, int (*cmpf)(const void *, const void *))
{
	/* Initialize it */
	rbtree->root = LDNS_RBTREE_NULL;
	rbtree->count = 0;
	rbtree->cmp = cmpf;
}
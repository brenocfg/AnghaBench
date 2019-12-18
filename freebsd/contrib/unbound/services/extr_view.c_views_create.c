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
struct views {int /*<<< orphan*/  vtree; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  lock_protect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lock_rw_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  view_cmp ; 

struct views* 
views_create(void)
{
	struct views* v = (struct views*)calloc(1, 
		sizeof(*v));
	if(!v)
		return NULL;
	rbtree_init(&v->vtree, &view_cmp);
	lock_rw_init(&v->lock);
	lock_protect(&v->lock, &v->vtree, sizeof(v->vtree));
	return v;
}
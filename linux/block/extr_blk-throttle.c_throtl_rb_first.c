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
struct throtl_service_queue {int /*<<< orphan*/  pending_tree; int /*<<< orphan*/  nr_pending; } ;
struct throtl_grp {int dummy; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct throtl_grp* rb_entry_tg (struct rb_node*) ; 
 struct rb_node* rb_first_cached (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct throtl_grp *
throtl_rb_first(struct throtl_service_queue *parent_sq)
{
	struct rb_node *n;
	/* Service tree is empty */
	if (!parent_sq->nr_pending)
		return NULL;

	n = rb_first_cached(&parent_sq->pending_tree);
	WARN_ON_ONCE(!n);
	if (!n)
		return NULL;
	return rb_entry_tg(n);
}
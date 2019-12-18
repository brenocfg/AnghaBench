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
struct TYPE_2__ {int /*<<< orphan*/ * first; int /*<<< orphan*/ ** last; } ;
struct idr {int num_size; int null_size; scalar_t__ pool_idx; TYPE_1__ wait_list; int /*<<< orphan*/  rbtree; } ;
struct archive_write {int dummy; } ;
struct archive_rb_tree_ops {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  __archive_rb_tree_init (int /*<<< orphan*/ *,struct archive_rb_tree_ops const*) ; 
 int idr_ensure_poolsize (struct archive_write*,struct idr*,int) ; 

__attribute__((used)) static int
idr_start(struct archive_write *a, struct idr *idr, int cnt, int ffmax,
    int num_size, int null_size, const struct archive_rb_tree_ops *rbt_ops)
{
	int r;

	(void)ffmax; /* UNUSED */

	r = idr_ensure_poolsize(a, idr, cnt);
	if (r != ARCHIVE_OK)
		return (r);
	__archive_rb_tree_init(&(idr->rbtree), rbt_ops);
	idr->wait_list.first = NULL;
	idr->wait_list.last = &(idr->wait_list.first);
	idr->pool_idx = 0;
	idr->num_size = num_size;
	idr->null_size = null_size;
	return (ARCHIVE_OK);
}
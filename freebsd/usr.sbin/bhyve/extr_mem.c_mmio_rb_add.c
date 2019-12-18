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
struct mmio_rb_tree {int dummy; } ;
struct mmio_rb_range {int /*<<< orphan*/  mr_end; int /*<<< orphan*/  mr_base; } ;

/* Variables and functions */
 int EEXIST ; 
 struct mmio_rb_range* RB_INSERT (int /*<<< orphan*/ ,struct mmio_rb_tree*,struct mmio_rb_range*) ; 
 int /*<<< orphan*/  mmio_rb_tree ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mmio_rb_add(struct mmio_rb_tree *rbt, struct mmio_rb_range *new)
{
	struct mmio_rb_range *overlap;

	overlap = RB_INSERT(mmio_rb_tree, rbt, new);

	if (overlap != NULL) {
#ifdef RB_DEBUG
		printf("overlap detected: new %lx:%lx, tree %lx:%lx\n",
		       new->mr_base, new->mr_end,
		       overlap->mr_base, overlap->mr_end);
#endif

		return (EEXIST);
	}

	return (0);
}
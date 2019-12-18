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
typedef  int /*<<< orphan*/  uint64_t ;
struct mmio_rb_tree {int dummy; } ;
struct mmio_rb_range {int /*<<< orphan*/  mr_end; int /*<<< orphan*/  mr_base; } ;

/* Variables and functions */
 int ENOENT ; 
 struct mmio_rb_range* RB_FIND (int /*<<< orphan*/ ,struct mmio_rb_tree*,struct mmio_rb_range*) ; 
 int /*<<< orphan*/  mmio_rb_tree ; 

__attribute__((used)) static int
mmio_rb_lookup(struct mmio_rb_tree *rbt, uint64_t addr,
    struct mmio_rb_range **entry)
{
	struct mmio_rb_range find, *res;

	find.mr_base = find.mr_end = addr;

	res = RB_FIND(mmio_rb_tree, rbt, &find);

	if (res != NULL) {
		*entry = res;
		return (0);
	}
	
	return (ENOENT);
}
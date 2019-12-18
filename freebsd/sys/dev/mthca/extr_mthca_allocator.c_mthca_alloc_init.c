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
typedef  int u32 ;
struct mthca_alloc {int max; int mask; int /*<<< orphan*/  table; int /*<<< orphan*/  lock; scalar_t__ top; scalar_t__ last; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int ffs (int) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mthca_alloc_init(struct mthca_alloc *alloc, u32 num, u32 mask,
		     u32 reserved)
{
	int i;

	/* num must be a power of 2 */
	if (num != 1 << (ffs(num) - 1))
		return -EINVAL;

	alloc->last = 0;
	alloc->top  = 0;
	alloc->max  = num;
	alloc->mask = mask;
	spin_lock_init(&alloc->lock);
	alloc->table = kmalloc(BITS_TO_LONGS(num) * sizeof (long),
			       GFP_KERNEL);
	if (!alloc->table)
		return -ENOMEM;

	bitmap_zero(alloc->table, num);
	for (i = 0; i < reserved; ++i)
		set_bit(i, alloc->table);

	return 0;
}
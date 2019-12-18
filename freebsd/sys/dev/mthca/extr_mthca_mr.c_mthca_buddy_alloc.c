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
struct mthca_buddy {int max_order; int /*<<< orphan*/  lock; scalar_t__* num_free; int /*<<< orphan*/ * bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 mthca_buddy_alloc(struct mthca_buddy *buddy, int order)
{
	int o;
	int m;
	u32 seg;

	spin_lock(&buddy->lock);

	for (o = order; o <= buddy->max_order; ++o)
		if (buddy->num_free[o]) {
			m = 1 << (buddy->max_order - o);
			seg = find_first_bit(buddy->bits[o], m);
			if (seg < m)
				goto found;
		}

	spin_unlock(&buddy->lock);
	return -1;

 found:
	clear_bit(seg, buddy->bits[o]);
	--buddy->num_free[o];

	while (o > order) {
		--o;
		seg <<= 1;
		set_bit(seg ^ 1, buddy->bits[o]);
		++buddy->num_free[o];
	}

	spin_unlock(&buddy->lock);

	seg <<= order;

	return seg;
}
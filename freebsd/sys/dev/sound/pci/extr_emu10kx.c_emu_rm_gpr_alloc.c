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
struct emu_rm {int num_gprs; int last_free_gpr; int* allocmap; int num_used; int /*<<< orphan*/  gpr_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
emu_rm_gpr_alloc(struct emu_rm *rm, int count)
{
	int i, j;
	int allocated_gpr;

	allocated_gpr = rm->num_gprs;
	/* try fast way first */
	mtx_lock(&(rm->gpr_lock));
	if (rm->last_free_gpr + count <= rm->num_gprs) {
		allocated_gpr = rm->last_free_gpr;
		rm->last_free_gpr += count;
		rm->allocmap[allocated_gpr] = count;
		for (i = 1; i < count; i++)
			rm->allocmap[allocated_gpr + i] = -(count - i);
	} else {
		/* longer */
		i = 0;
		allocated_gpr = rm->num_gprs;
		while (i < rm->last_free_gpr - count) {
			if (rm->allocmap[i] > 0) {
				i += rm->allocmap[i];
			} else {
				allocated_gpr = i;
				for (j = 1; j < count; j++) {
					if (rm->allocmap[i + j] != 0)
						allocated_gpr = rm->num_gprs;
				}
				if (allocated_gpr == i)
					break;
			}
		}
		if (allocated_gpr + count < rm->last_free_gpr) {
			rm->allocmap[allocated_gpr] = count;
			for (i = 1; i < count; i++)
				rm->allocmap[allocated_gpr + i] = -(count - i);

		}
	}
	if (allocated_gpr == rm->num_gprs)
		allocated_gpr = (-1);
	if (allocated_gpr >= 0)
		rm->num_used += count;
	mtx_unlock(&(rm->gpr_lock));
	return (allocated_gpr);
}
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
typedef  int /*<<< orphan*/  u_long ;
struct kvm_bitmap {int /*<<< orphan*/  size; int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/ * calloc (int /*<<< orphan*/ ,int) ; 

int
_kvm_bitmap_init(struct kvm_bitmap *bm, u_long bitmapsize, u_long *idx)
{

	*idx = ULONG_MAX;
	bm->map = calloc(bitmapsize, sizeof *bm->map);
	if (bm->map == NULL)
		return (0);
	bm->size = bitmapsize;
	return (1);
}
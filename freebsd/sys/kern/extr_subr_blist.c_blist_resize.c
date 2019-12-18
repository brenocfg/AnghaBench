#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ daddr_t ;
typedef  TYPE_1__* blist_t ;
struct TYPE_7__ {scalar_t__ bl_blocks; int /*<<< orphan*/  bl_radix; int /*<<< orphan*/  bl_root; } ;

/* Variables and functions */
 TYPE_1__* blist_create (scalar_t__,int) ; 
 int /*<<< orphan*/  blist_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  blist_free (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  blst_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 

void
blist_resize(blist_t *pbl, daddr_t count, int freenew, int flags)
{
    blist_t newbl = blist_create(count, flags);
    blist_t save = *pbl;

    *pbl = newbl;
    if (count > save->bl_blocks)
	    count = save->bl_blocks;
    blst_copy(save->bl_root, 0, save->bl_radix, newbl, count);

    /*
     * If resizing upwards, should we free the new space or not?
     */
    if (freenew && count < newbl->bl_blocks) {
	    blist_free(newbl, count, newbl->bl_blocks - count);
    }
    blist_destroy(save);
}
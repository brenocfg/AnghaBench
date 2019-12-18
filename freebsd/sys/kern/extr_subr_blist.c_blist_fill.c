#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ daddr_t ;
typedef  TYPE_1__* blist_t ;
struct TYPE_3__ {scalar_t__ bl_blocks; int /*<<< orphan*/  bl_avail; int /*<<< orphan*/  bl_radix; int /*<<< orphan*/  bl_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ blst_meta_fill (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

daddr_t
blist_fill(blist_t bl, daddr_t blkno, daddr_t count)
{
	daddr_t filled;

	KASSERT(blkno >= 0 && blkno + count <= bl->bl_blocks,
	    ("filling invalid range: blkno %jx, count %d, blocks %jd",
	    (uintmax_t)blkno, (int)count, (uintmax_t)bl->bl_blocks));
	filled = blst_meta_fill(bl->bl_root, blkno, count, bl->bl_radix);
	bl->bl_avail -= filled;
	return (filled);
}
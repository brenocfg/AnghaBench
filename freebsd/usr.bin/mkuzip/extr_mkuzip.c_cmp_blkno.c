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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ blkno; } ;
struct mkuz_blk {TYPE_1__ info; } ;

/* Variables and functions */

__attribute__((used)) static int
cmp_blkno(const struct mkuz_blk *bp, void *p)
{
	uint32_t *ap;

	ap = (uint32_t *)p;

	return (bp->info.blkno == *ap);
}
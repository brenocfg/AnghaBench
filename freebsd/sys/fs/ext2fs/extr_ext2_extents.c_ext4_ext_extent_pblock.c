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
struct ext4_extent {int e_start_lo; scalar_t__ e_start_hi; } ;
typedef  int e4fs_daddr_t ;

/* Variables and functions */

__attribute__((used)) static inline e4fs_daddr_t
ext4_ext_extent_pblock(struct ext4_extent *extent)
{
	e4fs_daddr_t blk;

	blk = extent->e_start_lo;
	blk |= (e4fs_daddr_t)extent->e_start_hi << 32;

	return (blk);
}
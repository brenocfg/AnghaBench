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
struct inode {scalar_t__ i_data; } ;
struct ext4_extent_header {unsigned short eh_depth; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned short
ext4_ext_inode_depth(struct inode *ip)
{
	struct ext4_extent_header *ehp;

	ehp = (struct ext4_extent_header *)ip->i_data;
	return (ehp->eh_depth);
}
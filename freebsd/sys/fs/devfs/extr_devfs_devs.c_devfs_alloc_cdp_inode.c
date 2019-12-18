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
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_unr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_inos ; 

ino_t
devfs_alloc_cdp_inode(void)
{

	return (alloc_unr(devfs_inos));
}
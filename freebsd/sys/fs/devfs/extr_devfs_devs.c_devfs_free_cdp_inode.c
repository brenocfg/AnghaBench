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
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  devfs_inos ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,scalar_t__) ; 

void
devfs_free_cdp_inode(ino_t ino)
{

	if (ino > 0)
		free_unr(devfs_inos, ino);
}
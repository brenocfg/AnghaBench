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
struct mount {int /*<<< orphan*/ * mnt_label; } ;

/* Variables and functions */
 int MPC_OBJECT_MOUNT ; 
 int mac_labeled ; 
 int /*<<< orphan*/ * mac_mount_label_alloc () ; 

void
mac_mount_init(struct mount *mp)
{

	if (mac_labeled & MPC_OBJECT_MOUNT)
		mp->mnt_label = mac_mount_label_alloc();
	else
		mp->mnt_label = NULL;
}
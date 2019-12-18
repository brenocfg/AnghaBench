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
struct ucred {int dummy; } ;
struct mount {int /*<<< orphan*/  mnt_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_POLICY_PERFORM (int /*<<< orphan*/ ,struct ucred*,struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_create ; 

void
mac_mount_create(struct ucred *cred, struct mount *mp)
{

	MAC_POLICY_PERFORM(mount_create, cred, mp, mp->mnt_label);
}
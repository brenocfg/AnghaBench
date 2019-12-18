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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int accmode_t ;

/* Variables and functions */
 int secpolicy_vnode_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
secpolicy_vnode_access2(cred_t *cr, vnode_t *vp, uid_t owner,
    accmode_t curmode, accmode_t wantmode)
{
	accmode_t mode;

	mode = ~curmode & wantmode;

	if (mode == 0)
		return (0);

	return (secpolicy_vnode_access(cr, vp, owner, mode));
}
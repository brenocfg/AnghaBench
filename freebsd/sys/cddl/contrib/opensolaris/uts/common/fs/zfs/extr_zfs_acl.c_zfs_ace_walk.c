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
typedef  int /*<<< orphan*/  zfs_acl_t ;
typedef  int /*<<< orphan*/  zfs_ace_hdr_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/ * zfs_acl_next_ace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t
zfs_ace_walk(void *datap, uint64_t cookie, int aclcnt,
    uint16_t *flags, uint16_t *type, uint32_t *mask)
{
	zfs_acl_t *aclp = datap;
	zfs_ace_hdr_t *acep = (zfs_ace_hdr_t *)(uintptr_t)cookie;
	uint64_t who;

	acep = zfs_acl_next_ace(aclp, acep, &who, mask,
	    flags, type);
	return ((uint64_t)(uintptr_t)acep);
}
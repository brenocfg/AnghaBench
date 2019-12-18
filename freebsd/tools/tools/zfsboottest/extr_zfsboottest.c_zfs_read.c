#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ zp_size; } ;
typedef  TYPE_1__ znode_phys_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  scalar_t__ off_t ;
struct TYPE_6__ {scalar_t__ dn_bonus; } ;
typedef  TYPE_2__ dnode_phys_t ;

/* Variables and functions */
 int dnode_read (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,void*,size_t) ; 

__attribute__((used)) static int
zfs_read(spa_t *spa, dnode_phys_t *dn, void *buf, size_t size, off_t off)
{
	const znode_phys_t *zp = (const znode_phys_t *) dn->dn_bonus;
	size_t n;
	int rc;

	n = size;
	if (off + n > zp->zp_size)
		n = zp->zp_size - off;

	rc = dnode_read(spa, dn, off, buf, n);
	if (rc != 0)
		return (-rc);

	return (n);
}
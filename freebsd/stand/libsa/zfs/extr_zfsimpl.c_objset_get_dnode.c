#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int off_t ;
struct TYPE_3__ {int /*<<< orphan*/  os_meta_dnode; } ;
typedef  TYPE_1__ objset_phys_t ;
typedef  int /*<<< orphan*/  dnode_phys_t ;

/* Variables and functions */
 int dnode_read (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
objset_get_dnode(const spa_t *spa, const objset_phys_t *os, uint64_t objnum, dnode_phys_t *dnode)
{
	off_t offset;

	offset = objnum * sizeof(dnode_phys_t);
	return dnode_read(spa, &os->os_meta_dnode, offset,
		dnode, sizeof(dnode_phys_t));
}
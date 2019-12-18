#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int rm_firstdatacol; } ;
typedef  TYPE_1__ raidz_map_t ;

/* Variables and functions */
 int /*<<< orphan*/  CE_PANIC ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vdev_raidz_generate_parity_p (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_raidz_generate_parity_pq (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_raidz_generate_parity_pqr (TYPE_1__*) ; 

__attribute__((used)) static void
vdev_raidz_generate_parity(raidz_map_t *rm)
{
	switch (rm->rm_firstdatacol) {
	case 1:
		vdev_raidz_generate_parity_p(rm);
		break;
	case 2:
		vdev_raidz_generate_parity_pq(rm);
		break;
	case 3:
		vdev_raidz_generate_parity_pqr(rm);
		break;
	default:
		cmn_err(CE_PANIC, "invalid RAID-Z configuration");
	}
}
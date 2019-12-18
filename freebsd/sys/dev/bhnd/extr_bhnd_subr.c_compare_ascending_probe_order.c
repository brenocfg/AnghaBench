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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BHND_BUS_GET_PROBE_ORDER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_ascending_probe_order(const void *lhs, const void *rhs)
{
	device_t	ldev, rdev;
	int		lorder, rorder;

	ldev = (*(const device_t *) lhs);
	rdev = (*(const device_t *) rhs);

	lorder = BHND_BUS_GET_PROBE_ORDER(device_get_parent(ldev), ldev);
	rorder = BHND_BUS_GET_PROBE_ORDER(device_get_parent(rdev), rdev);

	if (lorder < rorder) {
		return (-1);
	} else if (lorder > rorder) {
		return (1);
	} else {
		return (0);
	}
}
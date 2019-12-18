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
typedef  int /*<<< orphan*/  zfs_logbias_op_t ;
struct TYPE_3__ {int /*<<< orphan*/  os_logbias; } ;
typedef  TYPE_1__ objset_t ;

/* Variables and functions */

zfs_logbias_op_t
dmu_objset_logbias(objset_t *os)
{
	return (os->os_logbias);
}
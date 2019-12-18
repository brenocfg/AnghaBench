#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ zc_jailid; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
struct TYPE_5__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 TYPE_3__* curthread ; 
 int zone_dataset_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
zfs_ioc_jail(zfs_cmd_t *zc)
{

	return (zone_dataset_attach(curthread->td_ucred, zc->zc_name,
	    (int)zc->zc_jailid));
}
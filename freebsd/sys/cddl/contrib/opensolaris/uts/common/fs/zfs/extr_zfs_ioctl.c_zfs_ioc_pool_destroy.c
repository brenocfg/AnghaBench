#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;

/* Variables and functions */
 int spa_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_log_history (TYPE_1__*) ; 
 int /*<<< orphan*/  zvol_remove_minors (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_ioc_pool_destroy(zfs_cmd_t *zc)
{
	int error;
	zfs_log_history(zc);
	error = spa_destroy(zc->zc_name);
	if (error == 0)
		zvol_remove_minors(zc->zc_name);
	return (error);
}
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
struct sec_dev_info {size_t sec_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** sec_devices ; 
 int /*<<< orphan*/  sec_id_lock ; 

__attribute__((used)) static void sec_id_free(struct sec_dev_info *info)
{
	mutex_lock(&sec_id_lock);
	sec_devices[info->sec_id] = NULL;
	mutex_unlock(&sec_id_lock);
}
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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct g_raid_tr_object {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int
g_raid_tr_kerneldump_raid5(struct g_raid_tr_object *tr,
    void *virtual, vm_offset_t physical, off_t offset, size_t length)
{

	return (ENODEV);
}
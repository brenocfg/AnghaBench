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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_rlock_init (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline void
ocs_device_lock_init(ocs_t *ocs)
{
	ocs_rlock_init(ocs, &ocs->lock, "ocsdevicelock");
}
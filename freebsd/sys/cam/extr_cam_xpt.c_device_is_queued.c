#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ index; } ;
struct cam_ed {TYPE_1__ devq_entry; } ;

/* Variables and functions */
 scalar_t__ CAM_UNQUEUED_INDEX ; 

__attribute__((used)) static __inline int
device_is_queued(struct cam_ed *device)
{
	return (device->devq_entry.index != CAM_UNQUEUED_INDEX);
}
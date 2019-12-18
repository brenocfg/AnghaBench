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
struct TYPE_2__ {int status; } ;
union ccb {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int CAM_STATUS_MASK ; 

__attribute__((used)) static __inline int sym_get_cam_status(union ccb *ccb)
{
	return ccb->ccb_h.status & CAM_STATUS_MASK;
}
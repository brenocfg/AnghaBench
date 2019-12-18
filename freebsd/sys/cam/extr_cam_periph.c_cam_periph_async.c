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
typedef  int u_int32_t ;
struct cam_periph {int dummy; } ;
struct cam_path {int dummy; } ;

/* Variables and functions */
#define  AC_LOST_DEVICE 128 
 int /*<<< orphan*/  cam_periph_invalidate (struct cam_periph*) ; 

void
cam_periph_async(struct cam_periph *periph, u_int32_t code,
		 struct cam_path *path, void *arg)
{
	switch (code) {
	case AC_LOST_DEVICE:
		cam_periph_invalidate(periph);
		break; 
	default:
		break;
	}
}
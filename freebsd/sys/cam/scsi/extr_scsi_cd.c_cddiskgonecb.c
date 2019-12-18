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
struct disk {scalar_t__ d_drv1; } ;
struct cam_periph {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cam_periph_release (struct cam_periph*) ; 

__attribute__((used)) static void
cddiskgonecb(struct disk *dp)
{
	struct cam_periph *periph;

	periph = (struct cam_periph *)dp->d_drv1;
	cam_periph_release(periph);
}
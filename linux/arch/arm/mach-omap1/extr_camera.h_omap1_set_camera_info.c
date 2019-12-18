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
struct omap1_cam_platform_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap1_camera_init (struct omap1_cam_platform_data*) ; 

__attribute__((used)) static inline void omap1_set_camera_info(struct omap1_cam_platform_data *info)
{
	omap1_camera_init(info);
}
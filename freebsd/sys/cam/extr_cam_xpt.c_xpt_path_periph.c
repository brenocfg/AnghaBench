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
struct cam_periph {int dummy; } ;
struct cam_path {struct cam_periph* periph; } ;

/* Variables and functions */

struct cam_periph*
xpt_path_periph(struct cam_path *path)
{

	return (path->periph);
}
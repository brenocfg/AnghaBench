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
struct cam_path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (struct cam_path*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  M_CAMPATH ; 
 int /*<<< orphan*/  free (struct cam_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_path (struct cam_path*) ; 

void
xpt_free_path(struct cam_path *path)
{

	CAM_DEBUG(path, CAM_DEBUG_TRACE, ("xpt_free_path\n"));
	xpt_release_path(path);
	free(path, M_CAMPATH);
}
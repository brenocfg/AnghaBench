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
struct cam_path {TYPE_1__* bus; } ;
typedef  int /*<<< orphan*/  path_id_t ;
struct TYPE_2__ {int /*<<< orphan*/  path_id; } ;

/* Variables and functions */

path_id_t
xpt_path_path_id(struct cam_path *path)
{
	return(path->bus->path_id);
}
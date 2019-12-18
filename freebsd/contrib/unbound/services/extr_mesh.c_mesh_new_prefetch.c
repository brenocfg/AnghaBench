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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct query_info {int dummy; } ;
struct mesh_area {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mesh_schedule_prefetch (struct mesh_area*,struct query_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void mesh_new_prefetch(struct mesh_area* mesh, struct query_info* qinfo,
        uint16_t qflags, time_t leeway)
{
	mesh_schedule_prefetch(mesh, qinfo, qflags, leeway, 1);
}
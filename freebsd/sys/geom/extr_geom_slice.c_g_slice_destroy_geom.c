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
struct gctl_req {int dummy; } ;
struct g_geom {int /*<<< orphan*/  consumer; } ;
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_slice_spoiled (int /*<<< orphan*/ ) ; 

int
g_slice_destroy_geom(struct gctl_req *req, struct g_class *mp, struct g_geom *gp)
{

	g_slice_spoiled(LIST_FIRST(&gp->consumer));
	return (0);
}
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
struct g_part_parms {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,int) ; 

__attribute__((used)) static int
g_part_ctl_move(struct gctl_req *req, struct g_part_parms *gpp)
{
	gctl_error(req, "%d verb 'move'", ENOSYS);
	return (ENOSYS);
}
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

/* Variables and functions */
 int /*<<< orphan*/  GCTL_PARAM_RW ; 
 int /*<<< orphan*/  gctl_param_add (struct gctl_req*,char const*,int,void*,int /*<<< orphan*/ ) ; 

void
gctl_rw_param(struct gctl_req *req, const char *name, int len, void *value)
{

	gctl_param_add(req, name, len, value, GCTL_PARAM_RW);
}
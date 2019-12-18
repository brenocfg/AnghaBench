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
typedef  scalar_t__ u_int ;
struct ssh {int dummy; } ;
struct permission {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  permission_set_get_array (struct ssh*,int,int,struct permission***,scalar_t__**) ; 
 struct permission* xrecallocarray (struct permission*,scalar_t__,int /*<<< orphan*/ ,int) ; 

void
channel_clear_permission(struct ssh *ssh, int who, int where)
{
	struct permission **permp;
	u_int *npermp;

	permission_set_get_array(ssh, who, where, &permp, &npermp);
	*permp = xrecallocarray(*permp, *npermp, 0, sizeof(**permp));
	*npermp = 0;
}
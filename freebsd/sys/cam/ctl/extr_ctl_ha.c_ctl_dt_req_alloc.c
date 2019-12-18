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
struct ctl_ha_dt_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CTL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct ctl_ha_dt_req* malloc (int,int /*<<< orphan*/ ,int) ; 

struct ctl_ha_dt_req *
ctl_dt_req_alloc(void)
{

	return (malloc(sizeof(struct ctl_ha_dt_req), M_CTL, M_WAITOK | M_ZERO));
}